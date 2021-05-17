#pragma once

#include "canvas/Utils/ShaderSource.h"
#include "legion/Resources/Converters/RendererImporter.h"

namespace le {

class ShaderSourceImporter : public RendererImporter<ca::ShaderSource> {
  NU_DELETE_COPY_AND_MOVE(ShaderSourceImporter);

public:
  ShaderSourceImporter() = default;
  ~ShaderSourceImporter() override = default;

  bool import(nu::StringView name, nu::InputStream* stream, ca::ShaderSource* storage) override;
};

}  // namespace le
