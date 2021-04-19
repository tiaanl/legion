#include "legion/Resources/Converters/ModelConverter.h"

#include "hive/ResourceManager.h"

namespace le {

static void createMesh(ca::Renderer* renderer, const ca::VertexDefinition& vertexDefinition,
                       const si::Mesh& src, Mesh* dst) {
  dst->materialIndex = src.materialIndex;

  struct V {
    fl::Vec3 position;
    fl::Vec2 texCoords;
    ca::Color color;
  };

  DCHECK(src.positions.size() == src.texCoords.size());

  auto buffer = nu::DynamicArray<V>::withInitialCapacity(src.positions.size());
  for (MemSize i = 0; i < src.positions.size(); ++i) {
    buffer.emplaceBack(src.positions[i], src.texCoords[i], ca::Color::red);
  }

#if 0
  for (const auto& v : buffer) {
    LOG(Info) << "position = " << v.position << ", color = " << v.color
              << ", texCoords = " << v.texCoords;
  }
#endif

  dst->vertexBufferId =
      renderer->createVertexBuffer(vertexDefinition, buffer.data(), buffer.size() * sizeof(V));

  U32 vertexCount = static_cast<U32>(buffer.size());
  DCHECK(vertexCount % 3 == 0);

  dst->vertexCount = vertexCount;
  dst->drawType = ca::DrawType::Triangles;
}

void createMaterial(ca::Renderer* renderer, hi::ResourceManager* resourceManager,
                    const si::Material& src, Material* dst) {
  {
    // Diffuse
    dst->diffuse.color = ca::Color{
        static_cast<F32>(src.diffuse.color.red) / 255.0f,
        static_cast<F32>(src.diffuse.color.green) / 255.0f,
        static_cast<F32>(src.diffuse.color.blue) / 255.0f,
        static_cast<F32>(src.diffuse.color.alpha) / 255.0f,
    };

    if (!src.diffuse.texture.empty()) {
      dst->diffuse.texture = resourceManager->get<Texture>(src.diffuse.texture.view());
    }
  }

  dst->type = MaterialType::DiffuseColor;
  if (dst->diffuse.texture) {
    dst->type = MaterialType::Textured;

    auto vertexShader = resourceManager->get<ca::ShaderSource>("diffuse_texture.vs");
    auto fragmentShader = resourceManager->get<ca::ShaderSource>("diffuse_texture.fs");

    if (!vertexShader || !fragmentShader) {
      LOG(Error) << "Could not load shader. (diffuse_texture)";
    } else {
      dst->programId = renderer->createProgram(*vertexShader, *fragmentShader);
      dst->transformUniformId = renderer->createUniform("uTransform");
      dst->diffuse.textureUniformId = renderer->createUniform("uTexture");
    }
  } else {
    auto vertexShader = resourceManager->get<ca::ShaderSource>("diffuse_lopoly.vs");
    auto fragmentShader = resourceManager->get<ca::ShaderSource>("diffuse_lopoly.fs");

    if (!vertexShader || !fragmentShader) {
      LOG(Error) << "Could not load shader. (diffuse_lopoly)";
    } else {
      dst->programId = renderer->createProgram(*vertexShader, *fragmentShader);
      dst->transformUniformId = renderer->createUniform("uTransform");
    }
  }
}

static void createNode(const si::Node& src, ModelNode* dst) {
  dst->transform = src.transform;
  for (auto& meshIndex : src.meshIndices) {
    dst->meshIndices.emplaceBack(meshIndex);
  }

  for (const auto& childNode : src.children) {
    // dst->children.emplace_back(ca::Mat4::identity);
    // createNode(&childNode, &*dst->children.rbegin());
    auto result = dst->children.emplaceBack(fl::Mat4::identity);
    createNode(childNode, &result.element());
  }
}

ModelConverter::ModelConverter() {
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Four);
}

bool ModelConverter::load(hi::ResourceManager* resourceManager, nu::StringView NU_UNUSED(name),
                          nu::InputStream* inputStream, Model* model) {
  if (!m_renderer) {
    LOG(Error) << "Can not load geometry without a renderer.";
    return false;
  }

  si::Scene scene;
  if (!scene.load_from_collada(inputStream)) {
    LOG(Error) << "Could not load geometry ()";
    return false;
  }

  if (scene.meshes().isEmpty()) {
    LOG(Warning) << "Model contains no geometry.";
    return false;
  }

  // Add all the meshes.
  for (const auto& sceneMesh : scene.meshes()) {
    auto result = model->meshes.emplaceBack();
    createMesh(m_renderer, m_vertexDefinition, sceneMesh, &result.element());
  }

  // Add all materials.
  for (const auto& sceneMaterial : scene.materials()) {
    auto result = model->materials.emplaceBack();
    createMaterial(m_renderer, resourceManager, sceneMaterial, &result.element());
  }

  // Add nodes.
  createNode(scene.root_node(), &model->rootNode);

  return true;
}

}  // namespace le
