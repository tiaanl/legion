#include "legion/Resources/ResourceManager.h"

#include <utility>

namespace le {

ResourceManager::ResourceManager(nu::ScopedRefPtr<hi::Locator> locator)
  : locator_{std::move(locator)},
    image_resources_{locator_},
    scene_resources_{locator_},
    shader_source_resources_{locator_},
    model_resources_{locator_} {
  image_resources_.register_importer("png", nu::makeScopedPtr<PNGImageImporter>());
  scene_resources_.register_importer("dae", nu::makeScopedPtr<le::ColladaModelImporter>(this));
  shader_source_resources_.register_importer("glsl", nu::makeScopedPtr<ShaderSourceImporter>());
  model_resources_.register_importer("dae", nu::makeScopedPtr<le::RenderModelImporter>());
}

nu::ScopedPtr<si::Image> ResourceManager::get_image(nu::StringView name) {
  return image_resources_.import(name);
}
nu::ScopedPtr<si::Scene> ResourceManager::get_scene(nu::StringView name) {
  return scene_resources_.import(name);
}
nu::ScopedPtr<ca::ShaderSource> ResourceManager::get_shader_source(nu::StringView name) {
  return shader_source_resources_.import(name);
}

}  // namespace le
