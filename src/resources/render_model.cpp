#include "legion/resources/render_model.h"

#include <canvas/renderer/renderer.h>

#include "legion/resources/resource_manager.h"

namespace le {

static void createMesh(ca::Renderer* renderer, const ca::VertexDefinition& vertexDefinition,
                       const si::Mesh& src, Mesh* dst) {
  dst->materialIndex = src.material_index;

  struct V {
    fl::Vec3 position;
    fl::Vec2 texCoords;
    ca::Color color;
  };

  DCHECK(src.positions.size() == src.tex_coords.size() &&
         src.positions.size() == src.normals.size());

  auto buffer = nu::DynamicArray<V>::withInitialCapacity(src.positions.size());
  for (MemSize i = 0; i < src.positions.size(); ++i) {
    buffer.emplaceBack(src.positions[i], src.tex_coords[i], ca::Color::red);
  }

#if 0
  for (const auto& v : buffer) {
    LOG(Info) << "position = " << v.position << ", color = " << v.color
              << ", texCoords = " << v.texCoords;
  }
#endif

  dst->vertexBufferId =
      renderer->create_vertex_buffer(vertexDefinition, buffer.data(), buffer.size() * sizeof(V));

  U32 vertexCount = static_cast<U32>(buffer.size());
  DCHECK(vertexCount % 3 == 0);

  dst->vertexCount = vertexCount;
  dst->drawType = ca::DrawType::Triangles;
}

void createMaterial(ca::Renderer* renderer, le::ResourceManager* resourceManager,
                    const si::Material& src, Material* dst) {
  {
    // Diffuse
    dst->color = ca::Color{
        static_cast<F32>(src.diffuse.color.red) / 255.0f,
        static_cast<F32>(src.diffuse.color.green) / 255.0f,
        static_cast<F32>(src.diffuse.color.blue) / 255.0f,
        static_cast<F32>(src.diffuse.color.alpha) / 255.0f,
    };

    if (!src.diffuse.texture.empty()) {
      auto image = resourceManager->load_image(src.diffuse.texture.view());

      ca::TextureFormat textureFormat = ca::TextureFormat::Unknown;
      switch (image->format()) {
        case si::ImageFormat::RedGreenBlueAlpha:
          textureFormat = ca::TextureFormat::RGBA;
          break;

        case si::ImageFormat::RedGreenBlue:
          textureFormat = ca::TextureFormat::RGB;
          break;

        case si::ImageFormat::Alpha:
          textureFormat = ca::TextureFormat::Alpha;
          break;

        default:
          NOTREACHED();
          break;
      }

      auto textureId = renderer->create_texture(textureFormat, image->size(), image->data().data(),
                                                image->data().size(), false);
      if (!textureId.is_valid()) {
        return;
      }

      dst->texture.id = textureId;
      dst->texture.size = image->size();

      // TODO: Release the image when it is done uploading to the GPU.
      // resourceManager->release(image);
    }
  }

  dst->type = MaterialType::DiffuseColor;
  if (dst->texture.id.is_valid()) {
    dst->type = MaterialType::Textured;

    auto vertexShader = resourceManager->load_shader_source("diffuse_texture_v.glsl");
    auto fragmentShader = resourceManager->load_shader_source("diffuse_texture_f.glsl");

    if (!vertexShader || !fragmentShader) {
      LOG(Error) << "Could not load shader. (diffuse_texture)";
    } else {
      dst->programId = renderer->create_program(*vertexShader, *fragmentShader);
      dst->transformUniformId = renderer->create_uniform("uTransform");
      dst->textureUniformId = renderer->create_uniform("uTexture");
    }
  } else {
    auto vertexShader = resourceManager->load_shader_source("diffuse_lopoly_v.glsl");
    auto fragmentShader = resourceManager->load_shader_source("diffuse_lopoly_f.glsl");

    if (!vertexShader || !fragmentShader) {
      LOG(Error) << "Could not load shader. (diffuse_lopoly)";
    } else {
      dst->programId = renderer->create_program(*vertexShader, *fragmentShader);
      dst->transformUniformId = renderer->create_uniform("uTransform");
    }
  }
}

static void createNode(const si::Node& src, ModelNode* dst) {
  dst->set_transform(src.transform);
  for (auto& meshIndex : src.meshIndices) {
    dst->mesh_indices().emplaceBack(meshIndex);
  }

  for (const auto& childNode : src.children) {
    // dst->children.emplace_back(ca::Mat4::identity);
    // createNode(&childNode, &*dst->children.rbegin());
    auto result = dst->children().emplaceBack(fl::Mat4::identity);
    createNode(childNode, &result.element());
  }
}

RenderModel RenderModel::create_from_scene(si::Scene& scene, ResourceManager* resource_manager,
                                           ca::Renderer* renderer) {
  ca::VertexDefinition def;
  def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
  def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);
  def.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Four);

  RenderModel model;

  if (scene.meshes().empty()) {
    LOG(Warning) << "Model contains no geometry.";
    return {};
  }

  // Add all the meshes.
  for (const auto& sceneMesh : scene.meshes()) {
    auto result = model.meshes().emplaceBack();
    createMesh(renderer, def, sceneMesh, &result.element());
  }

  // Add all materials.
  for (const auto& sceneMaterial : scene.materials()) {
    auto result = model.materials().emplaceBack();
    createMaterial(renderer, resource_manager, sceneMaterial, &result.element());
  }

  // Add nodes.
  createNode(scene.root_node(), &model.root_node());

  return model;
}

}  // namespace le
