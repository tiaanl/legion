#pragma once
#include "canvas/Windows/event.h"
#include "canvas/Windows/mouse_event_handler_interface.h"
#include "legion/World/camera.h"

namespace le {

class CameraController {
  NU_DELETE_COPY_AND_MOVE(CameraController);

public:
  explicit CameraController(Camera* camera) : m_camera{camera} {}

  Camera* camera() const {
    return m_camera;
  }

  virtual void tick(F32 delta) = 0;

protected:
  Camera* m_camera;
};

}  // namespace le
