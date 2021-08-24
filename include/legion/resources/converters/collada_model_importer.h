#pragma once

#include "canvas/Renderer/renderer.h"
#include "legion/Resources/Converters/renderer_importer.h"
#include "legion/Resources/render_model.h"
#include "silhouette/scene.h"

namespace le {

class ResourceManager;

class ColladaModelImporter : public hi::Importer<si::Scene> {
public:
  explicit ColladaModelImporter(ResourceManager* resource_manager);

  bool import(nu::InputStream* stream, si::Scene* storage) override;

private:
  ResourceManager* resource_manager_;
  ca::VertexDefinition m_vertexDefinition;
};

}  // namespace le
