#pragma once

#include "legion/Resources/Converters/renderer_importer.h"
#include "legion/Resources/texture.h"

namespace le {

#if 0

class TextureConverter : public RendererImporter<Texture> {
  NU_DELETE_COPY_AND_MOVE(TextureConverter);

public:
  explicit TextureConverter() = default;
  ~TextureConverter() override = default;

  // Override: hi::Converter
  bool load(hi::ResourceManager* resourceManager, nu::StringView name, nu::InputStream* inputStream,
            Texture* storage) override;
};

#endif  // 0

}  // namespace le
