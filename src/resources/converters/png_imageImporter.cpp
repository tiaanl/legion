#include "legion/resources/converters/png_imageImporter.h"

#include "silhouette/codec/image/png.h"

namespace le {

bool PNGImageImporter::import(nu::StringView name, nu::InputStream* stream, si::Image* storage) {
  auto maybe_image = si::load_image_from_png(stream);
  if (!maybe_image.has_value()) {
    LOG(Warning) << "Could not load image. (" << name << ")";
    return false;
  }

  *storage = std::move(*maybe_image);

  return true;
}

}  // namespace le
