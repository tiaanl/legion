#ifndef AD_WORLD_TOP_DOWN_CAMERA_CONTROLLER_H_
#define AD_WORLD_TOP_DOWN_CAMERA_CONTROLLER_H_

#include "canvas/Math/Plane.h"
#include "legion/Controllers/CameraController.h"

namespace le {

class TopDownCameraController : public CameraController {
public:
  TopDownCameraController(Camera* camera, const ca::Plane& worldPlane, F32 height);

  void onMouseMoved(const ca::Vec2& position) override;
  void onMousePressed(ca::MouseEvent::Button button, const ca::Vec2& position) override;
  void onMouseReleased(ca::MouseEvent::Button button, const ca::Vec2& position) override;
  void onMouseWheel(const ca::Vec2& offset) override;
  void onKeyPressed(ca::Key key) override;
  void onKeyReleased(ca::Key key) override;
  void tick(F32 delta) override;

private:
  ca::Vec3 getMousePositionInWorld(const ca::Vec2& mousePosition) const;

  ca::Plane m_worldPlane;
  F32 m_height;

  struct {
    bool isMoving = false;
    ca::Vec3 lastMousePositionInWorld{ca::Vec3::zero};
    ca::Vec3 direction{ca::Vec3::zero};
  } m_movement;
};

}  // namespace le

#endif  // AD_WORLD_TOP_DOWN_CAMERA_CONTROLLER_H_
