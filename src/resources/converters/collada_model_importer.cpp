#include "legion/Resources/Converters/collada_model_importer.h"

#include <legion/Resources/resource_manager.h>

#include <silhouette/codec/scene/collada.hpp>

namespace le {

ColladaModelImporter::ColladaModelImporter(ResourceManager* resource_manager)
  : resource_manager_{resource_manager} {
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Four);
}

bool ColladaModelImporter::import(nu::StringView name, nu::InputStream* stream,
                                  si::Scene* storage) {
  auto maybe_scene = si::load_scene_from_collada(stream);
  if (!maybe_scene.has_value()) {
    LOG(Error) << "Could not load geometry";
    return false;
  }

  *storage = std::move(maybe_scene.value());

  return true;
}

}  // namespace le
