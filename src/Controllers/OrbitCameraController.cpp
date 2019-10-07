#include "legion/Controllers/OrbitCameraController.h"

namespace le {

OrbitCameraController::OrbitCameraController(Camera* camera, const ca::Vec3& origin)
  : CameraController{camera}, m_origin{origin} {}

void OrbitCameraController::onMouseMoved(const ca::Vec2& UNUSED(position)) {}

void OrbitCameraController::onMousePressed(ca::MouseEvent::Button UNUSED(button),
                                           const ca::Vec2& UNUSED(position)) {}

void OrbitCameraController::onMouseReleased(ca::MouseEvent::Button UNUSED(button),
                                            const ca::Vec2& UNUSED(position)) {}

void OrbitCameraController::onMouseWheel(const ca::Vec2& UNUSED(offset)) {}

void OrbitCameraController::onKeyPressed(ca::Key UNUSED(key)) {}

void OrbitCameraController::onKeyReleased(ca::Key UNUSED(key)) {}

void OrbitCameraController::tick(F32 UNUSED(delta)) {
  LOG(Info) << "moving camera";
  m_camera->moveTo(ca::Vec3{0.0f, 0.0f, 100.0f});
}

}  // namespace le
