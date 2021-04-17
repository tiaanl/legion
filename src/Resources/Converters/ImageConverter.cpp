#include "legion/Resources/Converters/ImageConverter.h"

namespace le {

bool ImageConverter::load(hi::ResourceManager* NU_UNUSED(resourceManager), nu::StringView name,
                          nu::InputStream* inputStream, si::Image* storage) {
  bool result = storage->load_from_png(inputStream);

  if (!result) {
    LOG(Warning) << "Could not load image. (" << name << ")";
    return false;
  }

  return true;
}

}  // namespace le
