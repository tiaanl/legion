#pragma once

#include <elastic/renderer/font.h>

#include "canvas/utils/shader_source.h"
#include "legion/resources/converters/renderer_importer.h"

namespace le {

class FontImporter : public renderer_importer<el::Font> {
  NU_DELETE_COPY_AND_MOVE(FontImporter);

public:
  FontImporter() = default;
  ~FontImporter() override = default;

  bool import(nu::StringView name, nu::InputStream* stream, el::Font* storage) override;
};

}  // namespace le
