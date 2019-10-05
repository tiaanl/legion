#ifndef LEGION_RESOURCES_CONVERTERS_RENDERER_CONVERTER_H_
#define LEGION_RESOURCES_CONVERTERS_RENDERER_CONVERTER_H_

#include "hive/Converter.h"

namespace ca {
class Renderer;
}  // namespace ca

namespace le {

template <typename ResourceType>
class RendererConverter : public hi::Converter<ResourceType> {
public:
  RendererConverter() = default;

  void setRenderer(ca::Renderer* renderer) {
    m_renderer = renderer;
  }

protected:
  ca::Renderer* m_renderer = nullptr;

private:
  DELETE_COPY_AND_MOVE(RendererConverter);
};

}  // namespace le

#endif  // LEGION_RESOURCES_CONVERTERS_RENDERER_CONVERTER_H_
