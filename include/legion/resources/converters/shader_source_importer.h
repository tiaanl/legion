#pragma once

#include "canvas/Utils/shader_source.h"
#include "legion/Resources/Converters/renderer_importer.h"

namespace le {

class ShaderSourceImporter : public renderer_importer<ca::ShaderSource> {
  NU_DELETE_COPY_AND_MOVE(ShaderSourceImporter);

public:
  ShaderSourceImporter() = default;
  ~ShaderSourceImporter() override = default;

  bool import(nu::StringView name, nu::InputStream* stream, ca::ShaderSource* storage) override;
};

}  // namespace le
