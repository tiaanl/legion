#include "legion/Resources/Converters/png_imageImporter.h"

namespace le {

bool PNGImageImporter::import(nu::StringView name, nu::InputStream* stream, si::Image* storage) {
  bool result = storage->load_from_png(stream);

  if (!result) {
    LOG(Warning) << "Could not load image. (" << name << ")";
    return false;
  }

  return true;
}

}  // namespace le
