#ifndef LEGION_WORLD_CAMERA_H_
#define LEGION_WORLD_CAMERA_H_

#include "canvas/Math/Angle.h"
#include "canvas/Math/Mat4.h"
#include "canvas/Math/Quaternion.h"
#include "canvas/Math/Ray.h"
#include "canvas/Math/Vec2.h"
#include "canvas/Utils/Pos.h"
#include "canvas/Utils/Size.h"

namespace le {

class Camera {
public:
  // Return clip space coordinates required for create a ray for mouse position.
  static ca::Vec2 convertScreenPositionToClipSpace(const ca::Pos& mousePosition,
                                                   const ca::Size& screenSize);

  static F32 aspectRatioFromScreenSize(const ca::Size& size);

  // Construct the camera with a world up vector.  The default up vector is the positive Y axis.
  explicit Camera(ca::Angle fieldOfView = ca::degrees(45.0f),
                  const ca::Vec3& worldUp = ca::Vec3::up, F32 aspectRatio = 1.0f);

  // Return the current aspect ratio.
  F32 aspectRatio() const {
    return m_aspectRatio;
  }

  // Set the camera's aspect ratio.
  void setAspectRatio(F32 aspectRatio);

  // Return the near plane for the camera frustum.
  F32 nearPlane() const {
    return m_nearPlane;
  }

  // Set the near plane.
  void setNearPlane(F32 nearPlane);

  // Return the far plane for the camera frustum.
  F32 farPlane() const {
    return m_farPlane;
  }

  // Set the far plane.
  void setFarPlane(F32 farPlane);

  // Return the field of view of the camera.
  ca::Angle fieldOfView() const {
    return m_fieldOfView;
  }

  // Set the camera's field of view.
  void setFieldOfView(ca::Angle fieldOfView);

  // Get the current position of the camera in world space.
  const ca::Vec3& position() const {
    return m_position;
  }

  // Move the camera to a fixed position in world space.
  void moveTo(const ca::Vec3& position);

  // Move the camera from it's current position by the `offset` given in world space.
  void moveBy(const ca::Vec3& offset);

  // Get the current orientation of the camera.
  const ca::Quaternion& orientation() const {
    return m_orientation;
  }

  // Set the camera's orientation to a fixed value.
  void rotateTo(const ca::Quaternion& orientation);

  // Apply the given axis and angle rotation to the current orientation of the camera.
  void rotateBy(const ca::Vec3& axis, ca::Angle angle);

  // Apply the given orientation to the current orientation of the camera.
  void rotateBy(const ca::Quaternion& orientation);

  // Return the camera's current forward vector.
  const ca::Vec3& forward() const {
    return m_forwardVector;
  }

  // Return the camera's current right vector.
  const ca::Vec3& right() const {
    return m_rightVector;
  }

  // Return the camera's current up vector.
  const ca::Vec3& up() const {
    return m_upVector;
  }

  // Create a ray that starts from the camera's current position and points towards the camera
  // forward direction.
  ca::Ray createRay() const;

  // Create a ray that starts from the camera's current position and points towards a mouse pointer
  // in clip space.
  // NOTE: The mouse position should be in the range: [-1.0f..1.0f]
  ca::Ray createRayForMouse(const ca::Vec2& mousePosition);

  // Update the given matrices with our projection and view matrices respectively.
  void updateProjectionMatrix(ca::Mat4* projectionMatrix);

  void updateViewMatrix(ca::Mat4* viewMatrix);

private:
  void invalidateProjection();

  void invalidateView();

  void updateProjectionMatrix();

  void updateViewMatrix();

  // The up vector of the world.
  ca::Vec3 m_worldUp;

  F32 m_nearPlane = 0.1f;
  F32 m_farPlane = 100.0f;

  ca::Angle m_fieldOfView;

  F32 m_aspectRatio = 1.0f;

  // The current position of the camera in world space.
  ca::Vec3 m_position{0.0f, 0.0f, 0.0f};

  // The current orientation of the camera.
  ca::Quaternion m_orientation = ca::Quaternion::identity;

  // Basis vectors.
  ca::Vec3 m_rightVector = ca::Vec3::right;
  ca::Vec3 m_upVector = ca::Vec3::up;
  ca::Vec3 m_forwardVector = ca::Vec3::forward;

  // Flags set to know which matrix needs updating.
  U32 m_dirtyFlags = 0u;

  ca::Mat4 m_projectionMatrix = ca::Mat4::identity;
  ca::Mat4 m_viewMatrix = ca::Mat4::identity;
};

}  // namespace le

#endif  // LEGION_WORLD_CAMERA_H_
