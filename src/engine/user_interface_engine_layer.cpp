#if 0
#include "legion/engine/user_interface_engine_layer.hpp"

namespace le {

el::Context& UserInterfaceEngineLayer::context() {
  return context_;
}

bool UserInterfaceEngineLayer::on_initialize() {
  if (!context_.initialize(&renderer())) {
    return false;
  }

  return true;
}

void UserInterfaceEngineLayer::on_resize(const fl::Size& size) {
  context_.resize(size);
}

void UserInterfaceEngineLayer::on_mouse_moved(const ca::MouseEvent& evt) {
  context_.on_mouse_moved(evt);
}

bool UserInterfaceEngineLayer::on_mouse_pressed(const ca::MouseEvent& evt) {
  return context_.on_mouse_pressed(evt);
}

void UserInterfaceEngineLayer::on_mouse_released(const ca::MouseEvent& evt) {
  context_.on_mouse_released(evt);
}

void UserInterfaceEngineLayer::on_mouse_wheel(const ca::MouseWheelEvent& evt) {
  context_.on_mouse_wheel(evt);
}

void UserInterfaceEngineLayer::on_key_pressed(const ca::KeyEvent& evt) {
  context_.on_key_pressed(evt);
}

void UserInterfaceEngineLayer::on_key_released(const ca::KeyEvent& evt) {
  context_.on_key_released(evt);
}

void UserInterfaceEngineLayer::update(F32 delta) {
  context_.tick(delta);
}

void UserInterfaceEngineLayer::on_render() {
  context_.render(&renderer());
}

}  // namespace le
#endif
