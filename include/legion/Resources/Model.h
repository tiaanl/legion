#pragma once

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"
#include "floats/Mat4.h"
#include "legion/Resources/Texture.h"
#include "nucleus/Containers/DynamicArray.h"

namespace le {

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
  Texture* texture;
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

class Model {
  NU_DELETE_COPY(Model);

public:
  Model() = default;
  ~Model() {
    LOG(Info) << "~Model";
  }

  Model(nu::DynamicArray<Mesh> meshes, nu::DynamicArray<Material> materials, ModelNode root_node)
    : meshes_{std::move(meshes)},
      materials_{std::move(materials)},
      root_node_{std::move(root_node)} {}

  NU_DEFAULT_MOVE(Model);

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
