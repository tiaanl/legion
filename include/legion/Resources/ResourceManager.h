#ifndef LEGION_RESOURCES_RESOURCE_MANAGER_H_
#define LEGION_RESOURCES_RESOURCE_MANAGER_H_

#include <hive/locator.h>
#include <hive/typed_resource.h>
#include <nucleus/Memory/ScopedRefPtr.h>

#include "legion/Resources/Converters/ColladaModelImporter.h"
#include "legion/Resources/Converters/PNGImageImporter.h"
#include "legion/Resources/Converters/ShaderSourceImporter.h"
#include "legion/Resources/Converters/TextureConverter.h"

namespace le {

using ShaderSourceResources = hi::TypedResource<ca::ShaderSource>;
using ImageResources = hi::TypedResource<si::Image>;
using SceneResources = hi::TypedResource<si::Scene>;
using ModelResources = hi::TypedResource<le::Model>;

class ResourceManager {
public:
  explicit ResourceManager(nu::ScopedRefPtr<hi::Locator> locator = {});

  nu::ScopedPtr<si::Image> get_image(nu::StringView name);
  nu::ScopedPtr<si::Scene> get_scene(nu::StringView name);
  nu::ScopedPtr<ca::ShaderSource> get_shader_source(nu::StringView name);

private:
  nu::ScopedRefPtr<hi::Locator> locator_;

  ImageResources image_resources_;
  SceneResources scene_resources_;
  ShaderSourceResources shader_source_resources_;
  ModelResources model_resources_;
};

}  // namespace le

#endif  // LEGION_RESOURCES_RESOURCE_MANAGER_H_
