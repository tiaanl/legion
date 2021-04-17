#ifndef LEGION_RESOURCES_CONVERTERS_SHADER_SOURCE_CONVERTER_H_
#define LEGION_RESOURCES_CONVERTERS_SHADER_SOURCE_CONVERTER_H_

#include "canvas/Utils/ShaderSource.h"
#include "legion/Resources/Converters/RendererConverter.h"

namespace le {

class ShaderSourceConverter : public RendererConverter<ca::ShaderSource> {
public:
  NU_DELETE_COPY_AND_MOVE(ShaderSourceConverter);

  ShaderSourceConverter() = default;
  ~ShaderSourceConverter() override = default;

private:
  bool load(hi::ResourceManager* resourceManager, nu::StringView name,
            nu::InputStream* inputStream, ca::ShaderSource* storage) override;
};

}  // namespace le

#endif  // LEGION_RESOURCES_CONVERTERS_SHADER_SOURCE_CONVERTER_H_
