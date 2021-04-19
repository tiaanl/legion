#include "legion/Controllers/OrbitCameraController.h"

namespace le {

OrbitCameraController::OrbitCameraController(Camera* camera, const fl::Vec3& origin)
  : CameraController{camera}, origin_{origin} {}

void OrbitCameraController::onMouseMoved(const fl::Vec2& position) {
  if (is_moving_camera_) {
    auto delta = drag_start_ - position;

    horizontal_ += fl::Angle::fromDegrees(delta.x);

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
  LOG(Info) << "tick " << horizontal_.degrees();
  m_camera->moveTo(fl::Vec3{horizontal_.degrees(), 0.0f, 10.0f});
}

}  // namespace le
