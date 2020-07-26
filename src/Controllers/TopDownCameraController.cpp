#include "legion/Controllers/TopDownCameraController.h"

#include "canvas/Math/Intersection.h"

namespace le {

// constexpr F32 kMouseSensitivity = 0.005f;
constexpr F32 kKeyboardSensitivity = 0.5f;

TopDownCameraController::TopDownCameraController(Camera* camera, const ca::Plane& worldPlane,
                                                 F32 height)
  : CameraController{camera}, m_worldPlane{worldPlane}, m_height{height} {}

void TopDownCameraController::tick(F32 delta) {
  auto pos = m_camera->position();
  m_camera->moveTo(ca::Vec3{pos.xy(), m_height});
  m_camera->moveBy(m_movement.direction * delta);
}

void TopDownCameraController::onMouseMoved(const ca::Vec2& position) {
  if (m_movement.isMoving) {
    ca::Vec3 newPositionInWorld = getMousePositionInWorld(position);
    ca::Vec3 worldDelta = m_movement.lastMousePositionInWorld - newPositionInWorld;

    m_camera->moveBy(worldDelta);
  }
}

void TopDownCameraController::onMousePressed(ca::MouseEvent::Button button,
                                             const ca::Vec2& position) {
  if (button == ca::MouseEvent::Button::Right) {
    m_movement.isMoving = true;
    m_movement.lastMousePositionInWorld = getMousePositionInWorld(position);
  }
}

void TopDownCameraController::onMouseReleased(ca::MouseEvent::Button button,
                                              const ca::Vec2& NU_UNUSED(position)) {
  if (button == ca::MouseEvent::Button::Right) {
    m_movement.isMoving = false;
  }
}

void TopDownCameraController::onMouseWheel(const ca::Vec2& offset) {
  // m_camera->setFieldOfView(m_camera->fieldOfView() + ca::degrees(-offset.y));
  m_height += -offset.y;
}

void TopDownCameraController::onKeyPressed(ca::Key key) {
  switch (key) {
    case ca::Key::A:
      m_movement.direction -= ca::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::D:
      m_movement.direction += ca::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::W:
      m_movement.direction += ca::Vec3::up * kKeyboardSensitivity;
      break;

    case ca::Key::S:
      m_movement.direction -= ca::Vec3::up * kKeyboardSensitivity;
      break;

    default:
      break;
  }
}

void TopDownCameraController::onKeyReleased(ca::Key key) {
  switch (key) {
    case ca::A:
      m_movement.direction += ca::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::D:
      m_movement.direction -= ca::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::W:
      m_movement.direction -= ca::Vec3::up * kKeyboardSensitivity;
      break;

    case ca::Key::S:
      m_movement.direction += ca::Vec3::up * kKeyboardSensitivity;
      break;

    default:
      break;
  }
}

ca::Vec3 TopDownCameraController::getMousePositionInWorld(const ca::Vec2& mousePosition) const {
  auto ray = m_camera->createRayForMouse(mousePosition);
  auto result = ca::intersection(m_worldPlane, ray);
  return result.position;
}

}  // namespace le
