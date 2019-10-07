#include "legion/World/Camera.h"

#include "canvas/Math/Common.h"
#include "canvas/Math/Intersection.h"
#include "canvas/Math/Transform.h"
#include "nucleus/Macros.h"

namespace le {

namespace {

enum class DirtyFlag : U32 {
  Projection = 0x0001u,
  View = 0x0002u,
};

}  // namespace

// static
ca::Vec2 Camera::convertScreenPositionToClipSpace(const ca::Pos& mousePosition,
                                                  const ca::Size& screenSize) {
  F32 x = (2.0f * static_cast<F32>(mousePosition.x) / static_cast<F32>(screenSize.width)) - 1.0f;
  F32 y = 1.0f - (2.0f * static_cast<F32>(mousePosition.y) / static_cast<F32>(screenSize.height));

  return {ca::clamp(x, -1.0f, 1.0f), ca::clamp(y, -1.0f, 1.0f)};
}

// static
F32 Camera::aspectRatioFromScreenSize(const ca::Size& size) {
  return (size.height > 0) ? static_cast<F32>(size.width) / static_cast<F32>(size.height) : 1.0f;
}

Camera::Camera(ca::Angle fieldOfView, const ca::Vec3& worldUp, F32 aspectRatio)
  : m_worldUp{ca::normalize(worldUp)}, m_fieldOfView{fieldOfView}, m_aspectRatio{aspectRatio} {
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

void Camera::setFieldOfView(ca::Angle fieldOfView) {
  m_fieldOfView = fieldOfView;
  invalidateProjection();
}

void Camera::moveTo(const ca::Vec3& position) {
  m_position = position;

  invalidateView();
}

void Camera::moveBy(const ca::Vec3& offset) {
  moveTo(m_position + offset);
}

void Camera::rotateTo(const ca::Quaternion& orientation) {
  m_orientation = orientation;

  invalidateView();
}

void Camera::rotateBy(const ca::Vec3& axis, ca::Angle angle) {
  rotateBy(ca::fromAxisAngle(axis, angle));
}

void Camera::rotateBy(const ca::Quaternion& orientation) {
  m_orientation = orientation * m_orientation;

  invalidateView();
}

ca::Ray Camera::createRay() const {
  return {m_position, m_forwardVector};
}

ca::Ray Camera::createRayForMouse(const ca::Vec2& mousePosition) {
  DCHECK(mousePosition.x >= -1.0f && mousePosition.x <= 1.0f);
  DCHECK(mousePosition.y >= -1.0f && mousePosition.y <= 1.0f);

  updateProjectionMatrix();
  updateViewMatrix();

  ca::Mat4 inverse = ca::inverse(m_projectionMatrix * m_viewMatrix);

  ca::Vec4 farPoint = inverse * ca::Vec4{mousePosition.x, mousePosition.y, -1.0f, 1.0f};
  ca::Vec4 midPoint = inverse * ca::Vec4{mousePosition.x, mousePosition.y, 0.0f, 1.0f};

  farPoint /= farPoint.w;
  midPoint /= midPoint.w;

  ca::Vec4 rayDirection = midPoint - farPoint;

  return ca::Ray{farPoint.xyz(), ca::normalize(rayDirection.xyz())};
}

void Camera::updateProjectionMatrix(ca::Mat4* projectionMatrix) {
  if (m_dirtyFlags & static_cast<U32>(DirtyFlag::Projection)) {
    m_dirtyFlags &= ~static_cast<U32>(DirtyFlag::Projection);
    updateProjectionMatrix();
  }

  *projectionMatrix = m_projectionMatrix;
}

void Camera::updateViewMatrix(ca::Mat4* viewMatrix) {
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
      ca::perspectiveProjection(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::updateViewMatrix() {
  m_viewMatrix = ca::createViewMatrix(m_position, m_orientation);

  ca::Mat4 t = ca::transpose(m_viewMatrix);

  m_rightVector = t.col[0].xyz();
  m_upVector = t.col[1].xyz();
  m_forwardVector = -t.col[2].xyz();
}

}  // namespace le
