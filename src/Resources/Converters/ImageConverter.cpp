#include "reactor/Resources/Converters/ImageConverter.h"

namespace re {

bool ImageConverter::load(hi::ResourceManager* UNUSED(resourceManager), const nu::StringView& name,
                          nu::InputStream* inputStream, si::Image* storage) {
  bool result = storage->loadFromStream(inputStream);

  if (!result) {
    LOG(Warning) << "Could not load image. (" << name << ")";
    return false;
  }

  return true;
}

}  // namespace re
