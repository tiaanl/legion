#include "legion/Controllers/OrbitCameraController.h"

#include <floats/Transform.h>

namespace le {

OrbitCameraController::OrbitCameraController(Camera* camera, const fl::Vec3& origin)
  : CameraController{camera}, origin_{origin} {}

void OrbitCameraController::onMouseMoved(const fl::Vec2& position) {
  if (is_moving_camera_) {
    auto delta = drag_start_ - position;

    horizontal_ += fl::Angle::fromDegrees(delta.x);
    vertical_ += fl::Angle::fromDegrees(delta.y);

    drag_start_ = position;
  }
}

void OrbitCameraController::onMousePressed(ca::MouseEvent::Button button,
                                           const fl::Vec2& position) {
  if (button == ca::MouseEvent::Button::Left) {
    is_moving_camera_ = true;
    drag_start_ = position;
  }
}

void OrbitCameraController::onMouseReleased(ca::MouseEvent::Button button,
                                            const fl::Vec2& NU_UNUSED(position)) {
  if (button == ca::MouseEvent::Button::Left) {
    is_moving_camera_ = false;
  }
}

void OrbitCameraController::onMouseWheel(const fl::Vec2& NU_UNUSED(offset)) {}

void OrbitCameraController::onKeyPressed(ca::Key NU_UNUSED(key)) {}

void OrbitCameraController::onKeyReleased(ca::Key NU_UNUSED(key)) {}

void OrbitCameraController::tick(F32 NU_UNUSED(delta)) {
  const F32 distance = 20.0f;

#if 0
  F32 x = fl::sine(horizontal_) * distance;
  F32 y = 0.0f; // fl::sine(vertical_) * distance;
  F32 z = fl::cosine(horizontal_) * distance;
#else
  F32 x = 0.0f;
  F32 y = fl::cosine(vertical_) * distance;
  F32 z = fl::sine(horizontal_) * distance;
#endif

  LOG(Info) << "X: " << x << ", Y: " << y << ", Z: " << z;

  m_camera->moveTo({x, y, z});

  m_camera->rotateTo(
      fl::Quaternion::fromEulerAngles(vertical_, fl::Angle::zero, fl::Angle::zero));
}

}  // namespace le
