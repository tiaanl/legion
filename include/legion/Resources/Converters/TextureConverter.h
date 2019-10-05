#ifndef LEGION_RESOURCES_CONVERTERS_TEXTURE_CONVERTER_H_
#define LEGION_RESOURCES_CONVERTERS_TEXTURE_CONVERTER_H_

#include "legion/Resources/Converters/RendererConverter.h"
#include "legion/Resources/Texture.h"

namespace le {

class TextureConverter : public RendererConverter<Texture> {
public:
  explicit TextureConverter() = default;
  ~TextureConverter() override = default;

  // Override: hi::Converter
  bool load(hi::ResourceManager* resourceManager, const nu::StringView& name,
            nu::InputStream* inputStream, Texture* storage) override;

private:
  DELETE_COPY_AND_MOVE(TextureConverter);
};

}  // namespace le

#endif  // LEGION_RESOURCES_CONVERTERS_TEXTURE_CONVERTER_H_
