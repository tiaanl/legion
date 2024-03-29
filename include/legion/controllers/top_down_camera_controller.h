#pragma once

#include "canvas/Windows/keyboard_event_receiver.h"
#include "floats/plane.h"
#include "legion/Controllers/camera_controller.h"

namespace le {

class TopDownCameraController : public CameraController,
                                public ca::MouseEventReceiver,
                                public ca::KeyboardEventReceiver {
public:
  TopDownCameraController(Camera* camera, const fl::Plane& worldPlane, F32 height);

  void set_screen_size(const fl::Size& size);

  // Override: CameraController
  void tick(F32 delta) override;

  // Override: ca::MouseEventHandlerInterface
  void on_mouse_moved(const ca::MouseEvent& evt) override;
  bool on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override;

  // Override: ca::KeyboardEventHandlerInterface
  void on_key_pressed(const ca::KeyEvent& evt) override;
  void on_key_released(const ca::KeyEvent& evt) override;

private:
  fl::Vec3 getMousePositionInWorld(const fl::Vec2& mousePosition) const;

  fl::Plane m_worldPlane;
  F32 m_height;
  fl::Size screen_size_ = {0, 0};

  struct {
    bool isMoving = false;
    fl::Vec3 lastMousePositionInWorld{fl::Vec3::zero};
    fl::Vec3 direction{fl::Vec3::zero};
  } m_movement;
};

}  // namespace le
