#include "legion/resources/resource_manager.h"

#include <utility>

#include "legion/resources/converters/font_importer.hpp"
#include "legion/resources/converters/obj_scene_importer.h"

namespace nu {

template <>
struct Hash<le::ResourceManager::FontKey> {
  static HashedValue hashed(const le::ResourceManager::FontKey& value) {
    return Hash<decltype(value.name)>::hashed(value.name) +
           Hash<decltype(value.size)>::hashed(value.size);
  }
};

}  // namespace nu

namespace le {

bool operator==(const ResourceManager::FontKey& left, const ResourceManager::FontKey& right) {
  return left.size == right.size && left.name == right.name;
}

ResourceManager::ResourceManager(nu::ScopedRefPtr<hi::Locator> locator, ca::Renderer* renderer)
  : locator_{std::move(locator)},
    renderer_{renderer},
    image_resources_{locator_},
    scene_resources_{locator_},
    shader_source_resources_{locator_} {
  image_resources_.register_importer("png", nu::make_scoped_ptr<PNGImageImporter>());
  scene_resources_.register_importer("dae", nu::make_scoped_ptr<le::ColladaModelImporter>(this));
  scene_resources_.register_importer("obj", nu::make_scoped_ptr<le::ObjSceneImporter>(this));
  shader_source_resources_.register_importer("glsl", nu::make_scoped_ptr<ShaderSourceImporter>());
}

bool ResourceManager::has_locator() const {
  return !locator_.is_null();
}

void ResourceManager::set_locator(nu::ScopedRefPtr<hi::Locator> locator) {
  locator_ = std::move(locator);

  image_resources_.set_locator(locator_);
  scene_resources_.set_locator(locator_);
  shader_source_resources_.set_locator(locator_);
}

void ResourceManager::set_renderer(ca::Renderer* renderer) {
  renderer_ = renderer;
}

nu::ScopedPtr<si::Image> ResourceManager::load_image(nu::StringView name) {
  return image_resources_.import(name);
}

nu::ScopedPtr<si::Scene> ResourceManager::load_scene(nu::StringView name) {
  return scene_resources_.import(name);
}

nu::ScopedPtr<ca::ShaderSource> ResourceManager::load_shader_source(nu::StringView name) {
  return shader_source_resources_.import(name);
}

Texture* ResourceManager::get_texture(nu::StringView name) {
  auto found = texture_resources_.find(name);
  if (found.was_found()) {
    return found.value().get();
  }

  auto image = load_image(name);
  if (!image) {
    return nullptr;
  }

  ca::TextureFormat textureFormat = ca::TextureFormat::Unknown;
  switch (image->format()) {
    case si::ImageFormat::RedGreenBlueAlpha:
      textureFormat = ca::TextureFormat::RGBA;
      break;

    case si::ImageFormat::RedGreenBlue:
      textureFormat = ca::TextureFormat::RGB;
      break;

    case si::ImageFormat::Alpha:
      textureFormat = ca::TextureFormat::Alpha;
      break;

    default:
      NOTREACHED();
      break;
  }

  auto textureId = renderer_->create_texture(textureFormat, image->size(), image->data().data(),
                                             image->data().size(), false);
  if (!textureId.is_valid()) {
    return nullptr;
  }

  auto result =
      texture_resources_.insert(name, nu::make_scoped_ptr<Texture>(textureId, image->size()));
  return result.value().get();
}

RenderModel* ResourceManager::get_render_model(nu::StringView name) {
  DCHECK(renderer_);

  auto found = render_model_resources_.find(name);
  if (found.was_found()) {
    return found.value().get();
  }

  auto scene = load_scene(name);
  if (!scene) {
    return nullptr;
  }

  RenderModel render_model = RenderModel::create_from_scene(*scene, this, renderer_);
  auto result = render_model_resources_.insert(
      name, nu::make_scoped_ptr<RenderModel>(std::move(render_model)));

  return result.value().get();
}

el::Font* ResourceManager::get_font(nu::StringView name, I32 size) {
  DCHECK(renderer_);

  FontKey key{name, size};

  auto found = font_resources_.find(key);
  if (found.was_found()) {
    return found.value().get();
  }

  auto font_stream = locator_->locate(name);
  if (!font_stream) {
    return nullptr;
  }

  auto font = nu::make_scoped_ptr<el::Font>();
  if (!font->load(font_stream.get(), renderer_, size)) {
    return nullptr;
  }

  auto result = font_resources_.insert(key, std::move(font));
  return result.value().get();
}

}  // namespace le
