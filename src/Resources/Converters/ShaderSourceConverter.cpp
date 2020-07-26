#include "legion/Resources/Converters/ShaderSourceConverter.h"

namespace le {

bool ShaderSourceConverter::load(hi::ResourceManager* NU_UNUSED(resourceManager),
                                 const nu::StringView& NU_UNUSED(name),
                                 nu::InputStream* inputStream, ca::ShaderSource* storage) {
  return storage->loadFromStream(inputStream);
}

}  // namespace le
