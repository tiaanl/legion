#pragma once

#include <canvas/Windows/window_delegate.h>
#include <nucleus/Memory/scoped_ptr.h>

#include "engine_layer.h"

namespace le {

class Engine;

class EngineWindowDelegate : public ca::WindowDelegate {
public:
  explicit EngineWindowDelegate(Engine* engine);
  ~EngineWindowDelegate() override;

  // Override ca::WindowDelegate
  bool onWindowCreated(ca::Window* window) override;
  void onWindowResized(const fl::Size& size) override;
  void on_mouse_moved(const ca::MouseEvent& evt) override;
  bool on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override;
  void on_key_pressed(const ca::KeyEvent& evt) override;
  void on_key_released(const ca::KeyEvent& evt) override;
  void tick(F32 delta) override;
  void onRender(ca::Renderer* renderer) override;

private:
  Engine* engine_;
  nu::ScopedPtr<EngineLayer> layer_;
};

}  // namespace le
