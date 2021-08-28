#include "legion/Controllers/top_down_camera_controller.h"

#include "floats/intersection.h"

namespace le {

// constexpr F32 kMouseSensitivity = 0.005f;
constexpr F32 kKeyboardSensitivity = 0.5f;

TopDownCameraController::TopDownCameraController(Camera* camera, const fl::Plane& worldPlane,
                                                 F32 height)
  : CameraController{camera}, m_worldPlane{worldPlane}, m_height{height} {}

void TopDownCameraController::set_screen_size(const fl::Size& size) {
  screen_size_ = size;
}

void TopDownCameraController::tick(F32 delta) {
  auto pos = m_camera->position();
  m_camera->moveTo(fl::Vec3{pos.xy(), m_height});
  m_camera->moveBy(m_movement.direction * delta);
}

void TopDownCameraController::on_mouse_moved(const ca::MouseEvent& evt) {
  if (m_movement.isMoving) {
    DCHECK(screen_size_.area() > 0);
    fl::Vec3 newPositionInWorld = getMousePositionInWorld(
        le::Camera::convertScreenPositionToClipSpace(evt.pos, screen_size_));
    fl::Vec3 worldDelta = m_movement.lastMousePositionInWorld - newPositionInWorld;

    m_camera->moveBy(worldDelta);
  }
}

bool TopDownCameraController::on_mouse_pressed(const ca::MouseEvent& evt) {
  if (evt.button == ca::MouseEvent::Button::Right) {
    DCHECK(screen_size_.area() > 0);
    m_movement.isMoving = true;
    m_movement.lastMousePositionInWorld = getMousePositionInWorld(
        le::Camera::convertScreenPositionToClipSpace(evt.pos, screen_size_));
    return true;
  }

  return false;
}

void TopDownCameraController::on_mouse_released(const ca::MouseEvent& evt) {
  if (evt.button == ca::MouseEvent::Button::Right) {
    m_movement.isMoving = false;
  }
}

void TopDownCameraController::on_mouse_wheel(const ca::MouseWheelEvent& evt) {
  // m_camera->setFieldOfView(m_camera->fieldOfView() + ca::degrees(-offset.y));
  m_height += -static_cast<F32>(evt.wheelOffset.y) * 5.0f;
}

void TopDownCameraController::on_key_pressed(const ca::KeyEvent& evt) {
  switch (evt.key) {
    case ca::Key::A:
      m_movement.direction -= fl::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::D:
      m_movement.direction += fl::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::W:
      m_movement.direction += fl::Vec3::forward * kKeyboardSensitivity;
      break;

    case ca::Key::S:
      m_movement.direction -= fl::Vec3::forward * kKeyboardSensitivity;
      break;

    default:
      break;
  }
}

void TopDownCameraController::on_key_released(const ca::KeyEvent& evt) {
  switch (evt.key) {
    case ca::A:
      m_movement.direction += fl::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::D:
      m_movement.direction -= fl::Vec3::right * kKeyboardSensitivity;
      break;

    case ca::Key::W:
      m_movement.direction -= fl::Vec3::forward * kKeyboardSensitivity;
      break;

    case ca::Key::S:
      m_movement.direction += fl::Vec3::forward * kKeyboardSensitivity;
      break;

    default:
      break;
  }
}
fl::Vec3 TopDownCameraController::getMousePositionInWorld(const fl::Vec2& mousePosition) const {
  auto ray = m_camera->createRayForMouse(mousePosition);
  auto result = fl::intersection(m_worldPlane, ray);
  return result.position;
}

}  // namespace le
