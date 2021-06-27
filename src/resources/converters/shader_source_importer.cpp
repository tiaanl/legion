#include "legion/Resources/Converters/shader_source_importer.h"

namespace le {

bool ShaderSourceImporter::import(nu::StringView name, nu::InputStream* stream,
                                  ca::ShaderSource* storage) {
  return storage->loadFromStream(stream);
}

}  // namespace le
