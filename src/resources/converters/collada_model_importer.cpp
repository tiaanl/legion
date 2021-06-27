#include "legion/Resources/Converters/collada_model_importer.h"

#include <legion/Resources/resource_manager.h>

namespace le {

ColladaModelImporter::ColladaModelImporter(ResourceManager* resource_manager)
  : resource_manager_{resource_manager} {
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Three);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Two);
  m_vertexDefinition.addAttribute(ca::ComponentType::Float32, ca::ComponentCount::Four);
}

bool ColladaModelImporter::import(nu::StringView name, nu::InputStream* stream,
                                  si::Scene* storage) {
  if (!storage->load_from_collada(stream)) {
    LOG(Error) << "Could not load geometry";
    return false;
  }

  return true;
}

}  // namespace le
