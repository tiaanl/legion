#ifndef LEGION_RESOURCES_CONVERTERS_IMAGE_CONVERTER_H_
#define LEGION_RESOURCES_CONVERTERS_IMAGE_CONVERTER_H_

#include "hive/Converter.h"
#include "silhouette/image.h"

namespace le {

class ImageConverter : public hi::Converter<si::Image> {
  NU_DELETE_COPY_AND_MOVE(ImageConverter);

public:
  ImageConverter() = default;

  // Override: hi::Converter
  bool load(hi::ResourceManager* resourceManager, nu::StringView name, nu::InputStream* inputStream,
            si::Image* storage) override;
};

}  // namespace le

#endif  // LEGION_RESOURCES_CONVERTERS_IMAGE_CONVERTER_H_
