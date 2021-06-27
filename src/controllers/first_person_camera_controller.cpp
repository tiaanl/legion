#include "legion/Controllers/first_person_camera_controller.h"

#include "legion/World/camera.h"

namespace le {

FirstPersonCameraController::FirstPersonCameraController(Camera* camera, F32 mouse_sensitivity,
                                                         F32 movement_speed)
  : CameraController{camera},
    mouse_sensitivity_{mouse_sensitivity},
    movement_speed_{movement_speed} {}

void FirstPersonCameraController::tick(F32 delta) {
  auto forward_movement = m_camera->forward() * m_moveDirection.y;
  auto right_movement = m_camera->right() * m_moveDirection.x;
  auto up_movement = m_camera->up() * m_moveDirection.z;

  m_camera->moveBy((forward_movement + right_movement + up_movement) * movement_speed_ * delta);
}

void FirstPersonCameraController::on_mouse_moved(const ca::MouseEvent& evt) {
  if (m_mouseIsDown) {
    const fl::Vec2 position{static_cast<F32>(evt.pos.x), static_cast<F32>(evt.pos.y)};

    fl::Vec2 delta{
        static_cast<F32>(position.x - m_lastMousePosition.x),
        static_cast<F32>(position.y - m_lastMousePosition.y),
    };

    m_yaw += -delta.x * mouse_sensitivity_;
    m_pitch += -delta.y * mouse_sensitivity_;

    m_camera->rotateTo(fl::Quaternion::fromEulerAngles(fl::degrees(m_pitch), fl::degrees(m_yaw),
                                                       fl::degrees(0.0f)));

    m_lastMousePosition = position;
  }
}

bool FirstPersonCameraController::on_mouse_pressed(const ca::MouseEvent& evt) {
  if (evt.button == ca::MouseEvent::Button::Left) {
    m_mouseIsDown = true;
    m_lastMousePosition = {static_cast<F32>(evt.pos.x), static_cast<F32>(evt.pos.y)};

    return true;
  }

  return false;
}

void FirstPersonCameraController::on_mouse_released(const ca::MouseEvent& evt) {
  if (evt.button == ca::MouseEvent::Button::Left) {
    m_mouseIsDown = false;
  }
}

void FirstPersonCameraController::on_mouse_wheel(const ca::MouseWheelEvent&) {}

void FirstPersonCameraController::on_key_pressed(const ca::KeyEvent& evt) {
  switch (evt.key) {
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

void FirstPersonCameraController::on_key_released(const ca::KeyEvent& evt) {
  switch (evt.key) {
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

}  // namespace le
