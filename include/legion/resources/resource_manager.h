#pragma once

#include <elastic/renderer/font.h>
#include <hive/locator/locator.h>
#include <hive/typed_resource.h>
#include <nucleus/Memory/scoped_ref_ptr.h>
#include <nucleus/hash.h>

#include "legion/Resources/Converters/collada_model_importer.h"
#include "legion/Resources/Converters/png_imageImporter.h"
#include "legion/Resources/Converters/shader_source_importer.h"

namespace le {

using ShaderSourceResources = hi::TypedResource<ca::ShaderSource>;
using ImageResources = hi::TypedResource<si::Image>;
using SceneResources = hi::TypedResource<si::Scene>;

class ResourceManager {
public:
  explicit ResourceManager(nu::ScopedRefPtr<hi::Locator> locator = {},
                           ca::Renderer* renderer = nullptr);

  bool has_locator() const;
  void set_locator(nu::ScopedRefPtr<hi::Locator> locator);

  void set_renderer(ca::Renderer* renderer);
  nu::ScopedPtr<si::Image> load_image(nu::StringView name);
  nu::ScopedPtr<si::Scene> load_scene(nu::StringView name);
  nu::ScopedPtr<ca::ShaderSource> load_shader_source(nu::StringView name);

  Texture* get_texture(nu::StringView name);
  RenderModel* get_render_model(nu::StringView name);
  el::Font* get_font(nu::StringView name, I32 size);

private:
  struct FontKey {
    nu::DynamicString name;
    I32 size;
  };

  friend struct nu::Hash<FontKey>;
  friend bool operator==(const FontKey&, const FontKey&);

  nu::ScopedRefPtr<hi::Locator> locator_;
  ca::Renderer* renderer_ = nullptr;

  ImageResources image_resources_;
  SceneResources scene_resources_;
  ShaderSourceResources shader_source_resources_;

  nu::HashMap<nu::DynamicString, nu::ScopedPtr<Texture>> texture_resources_;
  nu::HashMap<nu::DynamicString, nu::ScopedPtr<RenderModel>> render_model_resources_;
  nu::HashMap<FontKey, nu::ScopedPtr<el::Font>> font_resources_;
};

}  // namespace le
