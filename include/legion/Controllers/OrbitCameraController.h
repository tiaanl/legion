#ifndef AD_WORLD_ORBIT_CAMERA_CONTROLLER_H_
#define AD_WORLD_ORBIT_CAMERA_CONTROLLER_H_

#include "canvas/Windows/Event.h"
#include "legion/Controllers/CameraController.h"

namespace le {

class OrbitCameraController : public CameraController {
public:
  NU_DELETE_COPY_AND_MOVE(OrbitCameraController);

  OrbitCameraController(Camera* camera, const fl::Vec3& origin);

  // Override: CameraController
  void onMouseMoved(const fl::Vec2& position) override;
  void onMousePressed(ca::MouseEvent::Button button, const fl::Vec2& position) override;
  void onMouseReleased(ca::MouseEvent::Button button, const fl::Vec2& position) override;
  void onMouseWheel(const fl::Vec2& offset) override;
  void onKeyPressed(ca::Key key) override;
  void onKeyReleased(ca::Key key) override;
  void tick(F32 delta) override;

private:
  fl::Vec3 m_origin;
  fl::Angle m_horizontal = fl::Angle::zero;
  fl::Angle m_vertical = fl::Angle::zero;
};

}  // namespace le

#endif  // AD_WORLD_ORBIT_CAMERA_CONTROLLER_H_
