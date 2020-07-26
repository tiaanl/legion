#include "legion/Resources/Converters/TextureConverter.h"

#include "canvas/Renderer/Renderer.h"
#include "hive/ResourceManager.h"
#include "silhouette/Image/Image.h"

namespace le {

bool TextureConverter::load(hi::ResourceManager* resourceManager, const nu::StringView& name,
                            nu::InputStream* NU_UNUSED(inputStream), Texture* storage) {
  auto* image = resourceManager->get<si::Image>(name);

  auto textureId = m_renderer->createTexture(image->format(), image->size(), image->data(),
                                             image->dataSize(), false);
  if (!textureId.isValid()) {
    return false;
  }

  storage->id = textureId;
  storage->size = image->size();

  resourceManager->release(image);

  return true;
}

}  // namespace le
