#include "legion/Rendering/Rendering.h"

namespace le {

namespace {

void renderNode(ca::Renderer* renderer, const Model& model, const ModelNode& node,
                const fl::Mat4& transform) {
  fl::Mat4 t = transform * node.transform();

  for (auto meshIndex : node.mesh_indices()) {
    const Mesh& mesh = model.meshes()[meshIndex];
    const Material& material = model.materials()[mesh.materialIndex];

    // The material here might be null.

    // Set up the material.
    ca::UniformBuffer uniforms;
    uniforms.set(material.transformUniformId, t);

    if (material.type == MaterialType::Textured) {
      renderer->draw(mesh.drawType, 0, mesh.vertexCount, material.programId, mesh.vertexBufferId,
                     material.texture.id, uniforms);
    } else {
      renderer->draw(mesh.drawType, 0, mesh.vertexCount, material.programId, mesh.vertexBufferId,
                     {}, uniforms);
    }
  }

  for (const ModelNode& childNode : node.children()) {
    renderNode(renderer, model, childNode, t);
  }
}

}  // namespace

void renderModel(ca::Renderer* renderer, const Model& model, const fl::Mat4& transform) {
  renderNode(renderer, model, model.root_node(), transform);
}

}  // namespace le
