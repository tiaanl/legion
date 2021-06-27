#include "legion/Resources/Converters/texture_converter.h"

#include "canvas/Renderer/renderer.h"
#include "silhouette/image.h"

namespace le {

#if 0

bool TextureConverter::load(hi::ResourceManager* resourceManager, nu::StringView name,
                            nu::InputStream* NU_UNUSED(inputStream), Texture* storage) {
  auto* image = resourceManager->get<si::Image>(name);

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

  auto textureId = renderer_->createTexture(textureFormat, image->size(), image->data().data(),
                                             image->data().size(), false);
  if (!textureId.isValid()) {
    return false;
  }

  storage->id = textureId;
  storage->size = image->size();

  resourceManager->release(image);

  return true;
}

#endif  // 0

}  // namespace le
