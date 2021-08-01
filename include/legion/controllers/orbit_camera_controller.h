#pragma once

#include "canvas/windows/event.h"
#include "legion/controllers/camera_controller.h"

namespace le {

class OrbitCameraController : public CameraController, public ca::MouseEventReceiver {
public:
  NU_DELETE_COPY_AND_MOVE(OrbitCameraController);

  OrbitCameraController(Camera* camera, const fl::Vec3& origin);

  // Override: CameraController
  void on_mouse_moved(const ca::MouseEvent& event) override;
  bool on_mouse_pressed(const ca::MouseEvent& event) override;
  void on_mouse_released(const ca::MouseEvent& event) override;
  void on_mouse_wheel(const ca::MouseWheelEvent& event) override;
  void tick(F32 delta) override;

private:
  fl::Vec3 origin_;
  fl::Angle horizontal_ = fl::Angle::zero;
  fl::Angle vertical_ = fl::Angle::zero;

  bool is_moving_camera_ = false;
  fl::Vec2 drag_start_ = fl::Vec2::zero;
};

}  // namespace le
