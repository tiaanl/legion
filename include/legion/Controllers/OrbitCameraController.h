#ifndef AD_WORLD_ORBIT_CAMERA_CONTROLLER_H_
#define AD_WORLD_ORBIT_CAMERA_CONTROLLER_H_

#include "canvas/Windows/Event.h"
#include "legion/Controllers/CameraController.h"

namespace le {

class OrbitCameraController : public CameraController {
public:
  OrbitCameraController(Camera* camera, const ca::Vec3& origin);

  // Override: CameraController
  void onMouseMoved(const ca::Vec2& position) override;
  void onMousePressed(ca::MouseEvent::Button button, const ca::Vec2& position) override;
  void onMouseReleased(ca::MouseEvent::Button button, const ca::Vec2& position) override;
  void onMouseWheel(const ca::Vec2& offset) override;
  void onKeyPressed(ca::Key key) override;
  void onKeyReleased(ca::Key key) override;
  void tick(F32 delta) override;

private:
  DELETE_COPY_AND_MOVE(OrbitCameraController);

  ca::Vec3 m_origin;
  ca::Angle m_horizontal = ca::Angle::zero;
  ca::Angle m_vertical = ca::Angle::zero;
};

}  // namespace le

#endif  // AD_WORLD_ORBIT_CAMERA_CONTROLLER_H_
