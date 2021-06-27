#pragma once

#include "hive/importer.h"

namespace ca {
class Renderer;
}  // namespace ca

namespace le {

template <typename ResourceType>
class renderer_importer : public hi::Importer<ResourceType> {
public:
  ~renderer_importer() override = default;

  void renderer(ca::Renderer* renderer) {
    renderer_ = renderer;
  }

protected:
  ca::Renderer* renderer_ = nullptr;
};

}  // namespace le
