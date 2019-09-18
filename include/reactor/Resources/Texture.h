#ifndef REACTOR_RESOURCES_TEXTURE_H_
#define REACTOR_RESOURCES_TEXTURE_H_

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Size.h"

namespace re {

struct Texture {
  ca::TextureId id;
  ca::Size size;
};

}  // namespace re

#endif  // REACTOR_RESOURCES_TEXTURE_H_
