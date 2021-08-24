#pragma once

#include <canvas/renderer/renderer.h>
#include <silhouette/scene.h>

#include "legion/resources/converters/renderer_importer.h"
#include "legion/resources/render_model.h"

namespace le {

class ResourceManager;

class ObjSceneImporter : public hi::Importer<si::Scene> {
public:
  explicit ObjSceneImporter(ResourceManager* resource_manager);

  bool import(nu::InputStream* stream, si::Scene* storage) override;

private:
  ResourceManager* resource_manager_;
  ca::VertexDefinition m_vertexDefinition;
};

}  // namespace le
