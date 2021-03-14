#include "legion/Controllers/OrbitCameraController.h"

namespace le {

OrbitCameraController::OrbitCameraController(Camera* camera, const fl::Vec3& origin)
  : CameraController{camera}, m_origin{origin} {}

void OrbitCameraController::onMouseMoved(const fl::Vec2& NU_UNUSED(position)) {}

void OrbitCameraController::onMousePressed(ca::MouseEvent::Button NU_UNUSED(button),
                                           const fl::Vec2& NU_UNUSED(position)) {}

void OrbitCameraController::onMouseReleased(ca::MouseEvent::Button NU_UNUSED(button),
                                            const fl::Vec2& NU_UNUSED(position)) {}

void OrbitCameraController::onMouseWheel(const fl::Vec2& NU_UNUSED(offset)) {}

void OrbitCameraController::onKeyPressed(ca::Key NU_UNUSED(key)) {}

void OrbitCameraController::onKeyReleased(ca::Key NU_UNUSED(key)) {}

void OrbitCameraController::tick(F32 NU_UNUSED(delta)) {
  LOG(Info) << "moving camera";
  m_camera->moveTo(fl::Vec3{0.0f, 0.0f, 100.0f});
}

}  // namespace le
