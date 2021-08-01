#pragma once

#include <canvas/windows/window_delegate.h>
#include <nucleus/memory/scoped_ptr.h>

#include "engine_layer.h"

namespace le {

class Engine;

class EngineWindowDelegate : public ca::WindowDelegate {
public:
  explicit EngineWindowDelegate(Engine* engine);
  ~EngineWindowDelegate() override;

  // Override ca::WindowDelegate
  bool on_window_created(ca::Window* window) override;
  void on_window_resized(const fl::Size& size) override;
  void on_mouse_moved(const ca::MouseEvent& evt) override;
  bool on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override;
  void on_key_pressed(const ca::KeyEvent& evt) override;
  void on_key_released(const ca::KeyEvent& evt) override;
  void on_tick(F32 delta) override;
  void on_render(ca::Renderer* renderer) override;

private:
  Engine* engine_;
  nu::ScopedPtr<EngineLayer> layer_;
};

}  // namespace le
