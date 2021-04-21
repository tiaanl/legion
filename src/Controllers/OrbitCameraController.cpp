#include "legion/Controllers/OrbitCameraController.h"

#include <floats/Transform.h>

namespace le {

OrbitCameraController::OrbitCameraController(Camera* camera, const fl::Vec3& origin)
  : CameraController{camera}, origin_{origin} {}

void OrbitCameraController::on_mouse_moved(const ca::MouseEvent& event) {
  if (is_moving_camera_) {
    const auto position = fl::Vec2{static_cast<F32>(event.pos.x), static_cast<F32>(event.pos.y)};

    auto delta = drag_start_ - position;

    horizontal_ += fl::Angle::fromDegrees(delta.x);
    vertical_ += fl::Angle::fromDegrees(delta.y);

    drag_start_ = position;
  }
}

void OrbitCameraController::on_mouse_pressed(const ca::MouseEvent& event) {
  if (event.button == ca::MouseEvent::Button::Left) {
    const auto position = fl::Vec2{static_cast<F32>(event.pos.x), static_cast<F32>(event.pos.y)};

    is_moving_camera_ = true;
    drag_start_ = position;
  }
}

void OrbitCameraController::on_mouse_released(const ca::MouseEvent& event) {
  if (event.button == ca::MouseEvent::Button::Left) {
    is_moving_camera_ = false;
  }
}

void OrbitCameraController::on_mouse_wheel(const ca::MouseWheelEvent& NU_UNUSED(event)) {}

void OrbitCameraController::tick(F32 NU_UNUSED(delta)) {
  const F32 distance = 20.0f;

#if 1
  F32 x = fl::sine(horizontal_) * distance;
  F32 y = 0.0f;  // fl::sine(vertical_) * distance;
  F32 z = fl::cosine(horizontal_) * distance;
#else
  F32 x = 0.0f;
  F32 y = fl::cosine(vertical_) * distance;
  F32 z = fl::sine(horizontal_) * distance;
#endif

  // LOG(Info) << "X: " << x << ", Y: " << y << ", Z: " << z;

  m_camera->moveTo({x, y, z});
  m_camera->look_at(fl::Vec3::zero);
}

}  // namespace le
