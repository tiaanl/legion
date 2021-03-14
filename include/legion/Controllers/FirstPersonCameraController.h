#ifndef AD_FIRST_PERSON_CAMERA_INPUT_CONTROLLER_H_
#define AD_FIRST_PERSON_CAMERA_INPUT_CONTROLLER_H_

#include "floats/Vec3.h"
#include "legion/Controllers/CameraController.h"

namespace le {

class FirstPersonCameraController : public CameraController {
public:
  NU_DELETE_COPY_AND_MOVE(FirstPersonCameraController);

  explicit FirstPersonCameraController(Camera* camera, F32 mouseSensitivity = 1.0f);

  // Override: CameraController
  void onMouseMoved(const fl::Vec2& position) override;
  void onMousePressed(ca::MouseEvent::Button button, const fl::Vec2& position) override;
  void onMouseReleased(ca::MouseEvent::Button button, const fl::Vec2& position) override;
  void onMouseWheel(const fl::Vec2& offset) override;
  void onKeyPressed(ca::Key key) override;
  void onKeyReleased(ca::Key key) override;
  void tick(F32 delta) override;

private:
  // The speed at which the camera on mouse movement.
  F32 m_mouseSensitivity;

  // Keep track of the current pitch and yaw values that we pass to the camera.
  F32 m_yaw = 0.0f;
  F32 m_pitch = 0.0f;

  fl::Vec3 m_moveDirection{0.0f, 0.0f, 0.0f};

  bool m_mouseIsDown = false;
  fl::Vec2 m_lastMousePosition = fl::Vec2::zero;
};

}  // namespace le

#endif  // AD_FIRST_PERSON_CAMERA_INPUT_CONTROLLER_H_
