#include "legion/Controllers/FirstPersonCameraController.h"
#include "legion/World/Camera.h"

namespace le {

FirstPersonCameraController::FirstPersonCameraController(Camera* camera, F32 mouseSensitivity)
  : CameraController{camera}, m_mouseSensitivity{mouseSensitivity} {}

void FirstPersonCameraController::onMouseMoved(const ca::Vec2& position) {
  if (m_mouseIsDown) {
    ca::Vec2 delta{
        static_cast<F32>(position.x - m_lastMousePosition.x),
        static_cast<F32>(position.y - m_lastMousePosition.y),
    };

    m_yaw += -delta.x * m_mouseSensitivity;
    m_pitch += -delta.y * m_mouseSensitivity;

    m_camera->rotateTo(ca::Quaternion::fromEulerAngles(ca::degrees(m_pitch), ca::degrees(m_yaw),
                                                       ca::degrees(0.0f)));

    m_lastMousePosition = position;
  }
}

void FirstPersonCameraController::onMousePressed(ca::MouseEvent::Button button,
                                                 const ca::Vec2& position) {
  if (button == ca::MouseEvent::Button::Left) {
    m_mouseIsDown = true;
    m_lastMousePosition = position;
  }
}

void FirstPersonCameraController::onMouseReleased(ca::MouseEvent::Button button,
                                                  const ca::Vec2& UNUSED(position)) {
  if (button == ca::MouseEvent::Button::Left) {
    m_mouseIsDown = false;
  }
}

void FirstPersonCameraController::onMouseWheel(const ca::Vec2& UNUSED(offset)) {}

void FirstPersonCameraController::onKeyPressed(ca::Key key) {
  switch (key) {
    case ca::Key::A:
      m_moveDirection.x -= 1.0f;
      break;

    case ca::Key::D:
      m_moveDirection.x += 1.0f;
      break;

    case ca::Key::W:
      m_moveDirection.y += 1.0f;
      break;

    case ca::Key::S:
      m_moveDirection.y -= 1.0f;
      break;

    case ca::Key::Q:
      m_moveDirection.z += 1.0f;
      break;

    case ca::Key::Z:
      m_moveDirection.z -= 1.0f;
      break;

    default:
      break;
  }
}

void FirstPersonCameraController::onKeyReleased(ca::Key key) {
  switch (key) {
    case ca::Key::A:
      m_moveDirection.x += 1.0f;
      break;

    case ca::Key::D:
      m_moveDirection.x -= 1.0f;
      break;

    case ca::Key::W:
      m_moveDirection.y -= 1.0f;
      break;

    case ca::Key::S:
      m_moveDirection.y += 1.0;
      break;

    case ca::Key::Q:
      m_moveDirection.z -= 1.0f;
      break;

    case ca::Key::Z:
      m_moveDirection.z += 1.0f;
      break;

    default:
      break;
  }
}

void FirstPersonCameraController::tick(F32 delta) {
  constexpr F32 kMovementSpeed = 0.1f;

  auto forwardMovement = m_camera->forward() * m_moveDirection.y;
  auto rightMovement = m_camera->right() * m_moveDirection.x;
  auto upMovement = m_camera->up() * m_moveDirection.z;

  m_camera->moveBy((forwardMovement + rightMovement + upMovement) * kMovementSpeed * delta);
}

}  // namespace le
