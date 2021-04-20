#ifndef LEGION_WORLD_CAMERA_H_
#define LEGION_WORLD_CAMERA_H_

#include "floats/Angle.h"
#include "floats/Mat4.h"
#include "floats/Pos.h"
#include "floats/Quaternion.h"
#include "floats/Ray.h"
#include "floats/Size.h"
#include "floats/Vec2.h"

namespace le {

class Camera {
public:
  // Return clip space coordinates required for create a ray for mouse position.
  static fl::Vec2 convertScreenPositionToClipSpace(const fl::Pos& mousePosition,
                                                   const fl::Size& screenSize);

  static F32 aspectRatioFromScreenSize(const fl::Size& size);

  // Construct the camera with a world up vector.  The default up vector is the positive Y axis.
  explicit Camera(fl::Angle fieldOfView = fl::degrees(45.0f),
                  const fl::Vec3& worldUp = fl::Vec3::up, F32 aspectRatio = 1.0f);

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
  fl::Angle fieldOfView() const {
    return m_fieldOfView;
  }

  // Set the camera's field of view.
  void setFieldOfView(fl::Angle fieldOfView);

  // Get the current position of the camera in world space.
  const fl::Vec3& position() const {
    return m_position;
  }

  // Move the camera to a fixed position in world space.
  void moveTo(const fl::Vec3& position);

  // Move the camera from it's current position by the `offset` given in world space.
  void moveBy(const fl::Vec3& offset);

  // Get the current orientation of the camera.
  const fl::Quaternion& orientation() const {
    return m_orientation;
  }

  // Set the camera's orientation to a fixed value.
  void rotateTo(const fl::Quaternion& orientation);

  // Apply the given axis and angle rotation to the current orientation of the camera.
  void rotateBy(const fl::Vec3& axis, fl::Angle angle);

  // Apply the given orientation to the current orientation of the camera.
  void rotateBy(const fl::Quaternion& orientation);

  // Return the camera's current forward vector.
  const fl::Vec3& forward() const {
    return m_forwardVector;
  }

  // Return the camera's current right vector.
  const fl::Vec3& right() const {
    return m_rightVector;
  }

  // Return the camera's current up vector.
  const fl::Vec3& up() const {
    return m_upVector;
  }

  // Orient the camera to look at the target position.
  void look_at(const fl::Vec3& target);

  // Create a ray that starts from the camera's current position and points towards the camera
  // forward direction.
  fl::Ray createRay() const;

  // Create a ray that starts from the camera's current position and points towards a mouse pointer
  // in clip space.
  // NOTE: The mouse position should be in the range: [-1.0f..1.0f]
  fl::Ray createRayForMouse(const fl::Vec2& mousePosition);

  // Update the given matrices with our projection and view matrices respectively.
  void updateProjectionMatrix(fl::Mat4* projectionMatrix);

  void updateViewMatrix(fl::Mat4* viewMatrix);

private:
  void invalidateProjection();

  void invalidateView();

  void updateProjectionMatrix();

  void updateViewMatrix();

  // The up vector of the world.
  fl::Vec3 m_worldUp;

  F32 m_nearPlane = 0.1f;
  F32 m_farPlane = 100.0f;

  fl::Angle m_fieldOfView;

  F32 m_aspectRatio = 1.0f;

  // The current position of the camera in world space.
  fl::Vec3 m_position{0.0f, 0.0f, 0.0f};

  // The current orientation of the camera.
  fl::Quaternion m_orientation = fl::Quaternion::identity;

  // Basis vectors.
  fl::Vec3 m_rightVector = fl::Vec3::right;
  fl::Vec3 m_upVector = fl::Vec3::up;
  fl::Vec3 m_forwardVector = fl::Vec3::forward;

  // Flags set to know which matrix needs updating.
  U32 m_dirtyFlags = 0u;

  fl::Mat4 m_projectionMatrix = fl::Mat4::identity;
  fl::Mat4 m_viewMatrix = fl::Mat4::identity;
};

}  // namespace le

#endif  // LEGION_WORLD_CAMERA_H_
