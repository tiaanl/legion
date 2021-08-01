#include "legion/engine/engine_window_delegate.h"

#include <canvas/app.h>

#include "legion/engine/engine.hpp"

namespace le {

EngineWindowDelegate::EngineWindowDelegate(Engine* engine)
  : ca::WindowDelegate{"Legion"}, engine_{engine} {}

EngineWindowDelegate::~EngineWindowDelegate() = default;

bool EngineWindowDelegate::on_window_created(ca::Window* window) {
  if (!WindowDelegate::on_window_created(window)) {
    return false;
  }

  engine_->initialize(window->getRenderer());

  for (auto& layer : engine_->layers_) {
    layer->renderer_ = window->getRenderer();
    layer->resource_manager_ = &engine_->resource_manager_;
    if (!layer->on_initialize()) {
      return false;
    }
  }

  return true;
}

void EngineWindowDelegate::on_window_resized(const fl::Size& size) {
  for (auto& layer : engine_->layers_) {
    layer->on_resize(size);
  }
}

void EngineWindowDelegate::on_mouse_moved(const ca::MouseEvent& evt) {
  for (auto& layer : engine_->layers_) {
    layer->on_mouse_moved(evt);
  }
}

bool EngineWindowDelegate::on_mouse_pressed(const ca::MouseEvent& evt) {
  for (auto& layer : engine_->layers_) {
    if (layer->on_mouse_pressed(evt)) {
      return true;
    }
  }

  return false;
}

void EngineWindowDelegate::on_mouse_released(const ca::MouseEvent& evt) {
  for (auto& layer : engine_->layers_) {
    layer->on_mouse_released(evt);
  }
}

void EngineWindowDelegate::on_mouse_wheel(const ca::MouseWheelEvent& evt) {
  for (auto& layer : engine_->layers_) {
    layer->on_mouse_wheel(evt);
  }
}

void EngineWindowDelegate::on_key_pressed(const ca::KeyEvent& evt) {
  for (auto& layer : engine_->layers_) {
    layer->on_key_pressed(evt);
  }
}

void EngineWindowDelegate::on_key_released(const ca::KeyEvent& evt) {
  for (auto& layer : engine_->layers_) {
    layer->on_key_released(evt);
  }
}

void EngineWindowDelegate::on_tick(F32 delta) {
  for (auto& layer : engine_->layers_) {
    layer->update(delta);
  }
}

void EngineWindowDelegate::on_render(ca::Renderer* renderer) {
  for (auto& layer : engine_->layers_) {
    layer->on_render();
  }
}

}  // namespace le
