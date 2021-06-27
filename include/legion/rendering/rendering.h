#pragma once

#include "canvas/Renderer/renderer.h"
#include "legion/Resources/render_model.h"

namespace le {

void renderModel(ca::Renderer* renderer, const RenderModel& model, const fl::Mat4& transform);

}  // namespace le
