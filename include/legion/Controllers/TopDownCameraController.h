#ifndef AD_WORLD_TOP_DOWN_CAMERA_CONTROLLER_H_
#define AD_WORLD_TOP_DOWN_CAMERA_CONTROLLER_H_

#include "floats/Plane.h"
#include "legion/Controllers/CameraController.h"

namespace le {

class TopDownCameraController : public CameraController {
public:
  TopDownCameraController(Camera* camera, const fl::Plane& worldPlane, F32 height);

  void onMouseMoved(const fl::Vec2& position) override;
  void onMousePressed(ca::MouseEvent::Button button, const fl::Vec2& position) override;
  void onMouseReleased(ca::MouseEvent::Button button, const fl::Vec2& position) override;
  void onMouseWheel(const fl::Vec2& offset) override;
  void onKeyPressed(ca::Key key) override;
  void onKeyReleased(ca::Key key) override;
  void tick(F32 delta) override;

private:
  fl::Vec3 getMousePositionInWorld(const fl::Vec2& mousePosition) const;

  fl::Plane m_worldPlane;
  F32 m_height;

  struct {
    bool isMoving = false;
    fl::Vec3 lastMousePositionInWorld{fl::Vec3::zero};
    fl::Vec3 direction{fl::Vec3::zero};
  } m_movement;
};

}  // namespace le

#endif  // AD_WORLD_TOP_DOWN_CAMERA_CONTROLLER_H_
