#pragma once

#include "canvas/Windows/keyboard_event_handler_interface.h"
#include "canvas/Windows/mouse_event_handler_interface.h"
#include "floats/Vec3.h"
#include "legion/Controllers/camera_controller.h"

namespace le {

class FirstPersonCameraController : public CameraController,
                                    public ca::MouseEventHandlerInterface,
                                    public ca::KeyboardEventHandlerInterface {
public:
  NU_DELETE_COPY_AND_MOVE(FirstPersonCameraController);

  explicit FirstPersonCameraController(Camera* camera, F32 mouse_sensitivity = 1.0f,
                                       F32 movement_speed = 0.5f);

  // Override: CameraController
  void tick(F32 delta) override;

  // Override: ca::MouseEventHandlerInterface
  void on_mouse_moved(const ca::MouseEvent& evt) override;
  void on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override;

  // Override: ca::KeyboardEventHandlerInterface
  void on_key_pressed(const ca::KeyEvent& evt) override;
  void on_key_released(const ca::KeyEvent& evt) override;

private:
  // The speed at which the camera on mouse movement.
  F32 mouse_sensitivity_;

  // The speed at which the camera moves.
  F32 movement_speed_;

  // Keep track of the current pitch and yaw values that we pass to the camera.
  F32 m_yaw = 0.0f;
  F32 m_pitch = 0.0f;

  fl::Vec3 m_moveDirection{0.0f, 0.0f, 0.0f};

  bool m_mouseIsDown = false;
  fl::Vec2 m_lastMousePosition = fl::Vec2::zero;
};

}  // namespace le
