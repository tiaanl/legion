#include "legion/resources/converters/font_importer.hpp"

namespace le {

bool FontImporter::import(nu::StringView name, nu::InputStream* stream, el::Font* storage) {
  return storage->load(stream, renderer_, 10);
}

}  // namespace le
