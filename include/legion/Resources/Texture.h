#ifndef LEGION_RESOURCES_TEXTURE_H_
#define LEGION_RESOURCES_TEXTURE_H_

#include "canvas/Renderer/Types.h"
#include "floats/Size.h"

namespace le {

struct Texture {
  ca::TextureId id;
  fl::Size size;
};

}  // namespace le

#endif  // LEGION_RESOURCES_TEXTURE_H_
