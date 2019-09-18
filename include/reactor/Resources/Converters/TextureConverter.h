#ifndef REACTOR_RESOURCES_CONVERTERS_TEXTURE_CONVERTER_H_
#define REACTOR_RESOURCES_CONVERTERS_TEXTURE_CONVERTER_H_

#include "hive/Converter.h"
#include "reactor/Resources/Texture.h"

namespace ca {
class Renderer;
}  // namespace ca

namespace re {

class TextureConverter : public hi::Converter<Texture> {
public:
  explicit TextureConverter(ca::Renderer* renderer);

  // Override: hi::Converter
  bool load(hi::ResourceManager* resourceManager, const nu::StringView& name,
            nu::InputStream* inputStream, Texture* storage) override;

private:
  DELETE_COPY_AND_MOVE(TextureConverter);

  ca::Renderer* m_renderer;
};

}  // namespace re

#endif  // REACTOR_RESOURCES_CONVERTERS_TEXTURE_CONVERTER_H_
