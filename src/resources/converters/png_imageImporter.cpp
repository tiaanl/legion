#include "legion/resources/converters/png_imageImporter.h"

#include "silhouette/codec/image/png.h"

namespace le {

bool PNGImageImporter::import(nu::InputStream* stream, si::Image* storage) {
  auto maybe_image = si::load_image_from_png(stream);
  if (!maybe_image.has_value()) {
    return false;
  }

  *storage = std::move(*maybe_image);

  return true;
}

}  // namespace le
