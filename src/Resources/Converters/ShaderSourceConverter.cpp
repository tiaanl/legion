#include "legion/Resources/Converters/ShaderSourceConverter.h"

namespace le {

bool ShaderSourceConverter::load(hi::ResourceManager* UNUSED(resourceManager),
                                 const nu::StringView& name, nu::InputStream* inputStream,
                                 ca::ShaderSource* storage) {
  return storage->loadFromStream(inputStream);
}

}  // namespace le
