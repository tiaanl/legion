#ifndef LEGION_RESOURCES_MODEL_H_
#define LEGION_RESOURCES_MODEL_H_

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
  MaterialType type;

  ca::ProgramId programId;
  ca::UniformId transformUniformId;

  struct {
    ca::Color color = ca::Color::red;
    Texture* texture;
    ca::UniformId textureUniformId;
  } diffuse;
};

struct Mesh {
  MemSize materialIndex = 0;
  ca::DrawType drawType = ca::DrawType::Triangles;
  U32 vertexCount = 0;
  ca::VertexBufferId vertexBufferId;
};

struct ModelNode {
  fl::Mat4 transform;
  nu::DynamicArray<MemSize> meshIndices;
  // std::vector<Node> children;
  nu::DynamicArray<ModelNode> children;

  ModelNode() : transform(fl::Mat4::identity) {}
  explicit ModelNode(const fl::Mat4& transform) : transform{transform} {}
};

struct Model {
  nu::DynamicArray<Mesh> meshes;
  nu::DynamicArray<Material> materials;
  ModelNode rootNode;
};

}  // namespace le

#endif  // LEGION_RESOURCES_MODEL_H_
