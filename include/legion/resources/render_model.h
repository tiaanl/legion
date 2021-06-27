#pragma once

#include <silhouette/scene.h>

#include "canvas/Renderer/types.h"
#include "canvas/Utils/color.h"
#include "floats/mat4.h"
#include "legion/Resources/texture.h"
#include "nucleus/Containers/dynamic_array.h"

namespace ca {
class Renderer;
}  // namespace ca

namespace le {

class ResourceManager;

enum class MaterialType : U32 {
  DiffuseColor,
  Textured,
};

struct Material {
  Material() = default;

  NU_DEFAULT_MOVE(Material);

  MaterialType type;

  ca::ProgramId programId;
  ca::UniformId transformUniformId;

  ca::Color color = ca::Color::red;
  Texture texture;
  ca::UniformId textureUniformId;

private:
  NU_DELETE_COPY(Material);
};

struct Mesh {
  Mesh() = default;

  NU_DEFAULT_MOVE(Mesh);

  MemSize materialIndex = 0;
  ca::DrawType drawType = ca::DrawType::Triangles;
  U32 vertexCount = 0;
  ca::VertexBufferId vertexBufferId;

private:
  NU_DELETE_COPY(Mesh);
};

class ModelNode {
  NU_DELETE_COPY(ModelNode);

public:
  ModelNode() : transform_{fl::Mat4::identity} {}

  explicit ModelNode(const fl::Mat4& transform) : transform_{transform} {}

  // ModelNode(const fl::Mat4& transform, nu::DynamicArray<MemSize> mesh_indices,
  //          nu::DynamicArray<ModelNode>& children)
  //  : transform_{transform},
  //    mesh_indices_{std::move(mesh_indices)},
  //    children_{std::move(children)} {}

  NU_DEFAULT_MOVE(ModelNode);

  const fl::Mat4& transform() const {
    return transform_;
  }

  void set_transform(const fl::Mat4& transform) {
    transform_ = transform;
  }

  const nu::DynamicArray<MemSize>& mesh_indices() const {
    return mesh_indices_;
  }

  nu::DynamicArray<MemSize>& mesh_indices() {
    return mesh_indices_;
  }

  const nu::DynamicArray<ModelNode>& children() const {
    return children_;
  }

  nu::DynamicArray<ModelNode>& children() {
    return children_;
  }

private:
  fl::Mat4 transform_;
  nu::DynamicArray<MemSize> mesh_indices_;
  nu::DynamicArray<ModelNode> children_;
};

class RenderModel {
  NU_DELETE_COPY(RenderModel);

public:
  static RenderModel create_from_scene(si::Scene& scene, ResourceManager* resource_manager,
                                       ca::Renderer* renderer);

  RenderModel() = default;
  ~RenderModel() = default;

  RenderModel(nu::DynamicArray<Mesh> meshes, nu::DynamicArray<Material> materials,
              ModelNode root_node)
    : meshes_{std::move(meshes)},
      materials_{std::move(materials)},
      root_node_{std::move(root_node)} {}

  NU_DEFAULT_MOVE(RenderModel);

  nu::DynamicArray<Mesh>& meshes() {
    return meshes_;
  }

  const nu::DynamicArray<Mesh>& meshes() const {
    return meshes_;
  }

  nu::DynamicArray<Material>& materials() {
    return materials_;
  }

  const nu::DynamicArray<Material>& materials() const {
    return materials_;
  }

  ModelNode& root_node() {
    return root_node_;
  }

  const ModelNode& root_node() const {
    return root_node_;
  }

private:
  nu::DynamicArray<Mesh> meshes_;
  nu::DynamicArray<Material> materials_;
  ModelNode root_node_;
};

}  // namespace le
