#ifndef LEGION_RESOURCES_TEXTURE_H_
#define LEGION_RESOURCES_TEXTURE_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Size.h"

namespace le {

struct Texture {
  ca::TextureId id;
  ca::Size size;
};

}  // namespace le

#endif  // LEGION_RESOURCES_TEXTURE_H_
