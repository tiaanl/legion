#ifndef LEGION_RENDERING_RENDERING_H_
#define LEGION_RENDERING_RENDERING_H_

#include "canvas/Renderer/Renderer.h"
#include "legion/Resources/Model.h"

namespace le {

void renderModel(ca::Renderer* renderer, const Model& model, const ca::Mat4& transform);

}  // namespace le

#endif  // LEGION_RENDERING_RENDERING_H_
