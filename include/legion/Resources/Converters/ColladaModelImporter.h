#ifndef LEGION_RESOURCES_CONVERTERS_MODEL_CONVERTER_H_
#define LEGION_RESOURCES_CONVERTERS_MODEL_CONVERTER_H_

#include "canvas/Renderer/Renderer.h"
#include "legion/Resources/Converters/RendererImporter.h"
#include "legion/Resources/Model.h"
#include "silhouette/scene.h"

namespace le {

class ResourceManager;

class ColladaModelImporter : public hi::Importer<si::Scene> {
public:
  explicit ColladaModelImporter(ResourceManager* resource_manager);

  bool import(nu::StringView name, nu::InputStream* stream, si::Scene* storage) override;

private:
  ResourceManager* resource_manager_;
  ca::VertexDefinition m_vertexDefinition;
};

}  // namespace le

#endif  // LEGION_RESOURCES_CONVERTERS_MODEL_CONVERTER_H_
