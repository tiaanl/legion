#ifndef REACTOR_RESOURCES_CONVERTERS_IMAGE_CONVERTER_H_
#define REACTOR_RESOURCES_CONVERTERS_IMAGE_CONVERTER_H_

#include "hive/Converter.h"
#include "silhouette/Image/Image.h"

namespace re {

class ImageConverter : public hi::Converter<si::Image> {
public:
  // Override: hi::Converter
  bool load(hi::ResourceManager* resourceManager, const nu::StringView& name,
            nu::InputStream* inputStream, si::Image* storage) override;

private:
  DELETE_COPY_AND_MOVE(ImageConverter);
};

}  // namespace re

#endif  // REACTOR_RESOURCES_CONVERTERS_IMAGE_CONVERTER_H_
