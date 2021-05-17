#include "legion/Resources/Converters/ShaderSourceImporter.h"

namespace le {

bool ShaderSourceImporter::import(nu::StringView name, nu::InputStream* stream,
                                  ca::ShaderSource* storage) {
  return storage->loadFromStream(stream);
}

}  // namespace le
