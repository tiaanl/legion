#if 0
#pragma once

#include <elastic/context.h>

#include "engine_layer.h"

namespace le {

class UserInterfaceEngineLayer : public EngineLayer {
public:
  ~UserInterfaceEngineLayer() override = default;

protected:
  el::Context& context();

  // Override: EngineLayer
  bool on_initialize() override;
  void on_resize(const fl::Size& size) override;
  void on_mouse_moved(const ca::MouseEvent& evt) override;
  bool on_mouse_pressed(const ca::MouseEvent& evt) override;
  void on_mouse_released(const ca::MouseEvent& evt) override;
  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override;
  void on_key_pressed(const ca::KeyEvent& evt) override;
  void on_key_released(const ca::KeyEvent& evt) override;
  void update(F32 delta) override;
  void on_render() override;

private:
  el::Context context_;
};

}  // namespace le
#endif  // 0
