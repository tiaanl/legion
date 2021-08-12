#include "legion/resources/converters/obj_scene_importer.h"

#include <silhouette/codec/scene/obj.h>

#include "legion/resources/resource_manager.h"

namespace le {

ObjSceneImporter::ObjSceneImporter(ResourceManager* resource_manager)
  : resource_manager_{resource_manager} {
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Four);
}

bool ObjSceneImporter::import(nu::StringView name, nu::InputStream* stream, si::Scene* storage) {
  auto maybe_scene = si::load_scene_from_obj(stream);
  if (!maybe_scene.has_value()) {
    LOG(Error) << "Could not load geometry";
    return false;
  }

  *storage = std::move(*maybe_scene);

  return true;
}

}  // namespace le
