#pragma once

#include <elastic/Renderer/font.h>

#include "canvas/Utils/shader_source.h"
#include "legion/Resources/Converters/renderer_importer.h"

namespace le {

class FontImporter : public renderer_importer<el::Font> {
  NU_DELETE_COPY_AND_MOVE(FontImporter);

public:
  FontImporter() = default;
  ~FontImporter() override = default;

  bool import(nu::StringView name, nu::InputStream* stream, el::Font* storage) override;
};

}  // namespace le
