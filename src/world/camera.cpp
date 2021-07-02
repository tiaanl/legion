#include "legion/World/camera.h"

#include "floats/common.h"
#include "floats/intersection.h"
#include "floats/transform.h"
#include "nucleus/macros.h"

namespace le {

namespace {

enum class DirtyFlag : U32 {
  Projection = 0x0001u,
  View = 0x0002u,
};

}  // namespace

// static
fl::Vec2 Camera::convertScreenPositionToClipSpace(const fl::Pos& mousePosition,
                                                  const fl::Size& screenSize) {
  F32 x = (2.0f * static_cast<F32>(mousePosition.x) / static_cast<F32>(screenSize.width)) - 1.0f;
  F32 y = 1.0f - (2.0f * static_cast<F32>(mousePosition.y) / static_cast<F32>(screenSize.height));

  return {fl::clamp(x, -1.0f, 1.0f), fl::clamp(y, -1.0f, 1.0f)};
}

// static
F32 Camera::aspectRatioFromScreenSize(const fl::Size& size) {
  return (size.height > 0) ? static_cast<F32>(size.width) / static_cast<F32>(size.height) : 1.0f;
}

Camera::Camera(fl::Angle fieldOfView, const fl::Vec3& worldUp, F32 aspectRatio)
  : m_worldUp{fl::normalize(worldUp)}, m_fieldOfView{fieldOfView}, m_aspectRatio{aspectRatio} {
  updateProjectionMatrix();
  updateViewMatrix();
}

void Camera::setAspectRatio(F32 aspectRatio) {
  m_aspectRatio = aspectRatio;
  invalidateProjection();
}

void Camera::setNearPlane(F32 nearPlane) {
  m_nearPlane = nearPlane;
  invalidateProjection();
}

void Camera::setFarPlane(F32 farPlane) {
  m_farPlane = farPlane;
  invalidateProjection();
}

void Camera::setFieldOfView(fl::Angle fieldOfView) {
  m_fieldOfView = fieldOfView;
  invalidateProjection();
}

void Camera::moveTo(const fl::Vec3& position) {
  m_position = position;

  invalidateView();
}

void Camera::moveBy(const fl::Vec3& offset) {
  moveTo(m_position + offset);
}

void Camera::rotateTo(const fl::Quaternion& orientation) {
  m_orientation = orientation;

  invalidateView();
}

void Camera::rotateBy(const fl::Vec3& axis, fl::Angle angle) {
  rotateBy(fl::fromAxisAngle(axis, angle));
}

void Camera::rotateBy(const fl::Quaternion& orientation) {
  m_orientation = orientation * m_orientation;

  invalidateView();
}

fl::Ray Camera::createRay() const {
  return {m_position, m_forwardVector};
}

fl::Ray Camera::createRayForMouse(const fl::Vec2& mousePosition) {
  DCHECK(mousePosition.x >= -1.0f && mousePosition.x <= 1.0f);
  DCHECK(mousePosition.y >= -1.0f && mousePosition.y <= 1.0f);

  updateProjectionMatrix();
  updateViewMatrix();

  fl::Mat4 inverse = fl::inverse(m_projectionMatrix * m_viewMatrix);

  fl::Vec4 farPoint = inverse * fl::Vec4{mousePosition.x, mousePosition.y, -1.0f, 1.0f};
  fl::Vec4 midPoint = inverse * fl::Vec4{mousePosition.x, mousePosition.y, 0.0f, 1.0f};

  farPoint /= farPoint.w;
  midPoint /= midPoint.w;

  fl::Vec4 rayDirection = midPoint - farPoint;

  return fl::Ray{farPoint.xyz(), fl::normalize(rayDirection.xyz())};
}

void Camera::updateProjectionMatrix(fl::Mat4* projectionMatrix) {
  if (m_dirtyFlags & static_cast<U32>(DirtyFlag::Projection)) {
    m_dirtyFlags &= ~static_cast<U32>(DirtyFlag::Projection);
    updateProjectionMatrix();
  }

  *projectionMatrix = m_projectionMatrix;
}

void Camera::updateViewMatrix(fl::Mat4* viewMatrix) {
  if (m_dirtyFlags & static_cast<U32>(DirtyFlag::View)) {
    m_dirtyFlags &= ~static_cast<U32>(DirtyFlag::View);
    updateViewMatrix();
  }

  *viewMatrix = m_viewMatrix;
}

void Camera::invalidateProjection() {
  m_dirtyFlags |= static_cast<U32>(DirtyFlag::Projection);
}

void Camera::invalidateView() {
  m_dirtyFlags |= static_cast<U32>(DirtyFlag::View);
}

void Camera::updateProjectionMatrix() {
  m_projectionMatrix =
      fl::perspective_projection(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::updateViewMatrix() {
  m_viewMatrix = fl::create_view_matrix(m_position, m_orientation);

  fl::Mat4 t = fl::transpose(m_viewMatrix);

  m_rightVector = t.col[0].xyz();
  m_upVector = t.col[1].xyz();
  m_forwardVector = -t.col[2].xyz();
}

}  // namespace le
