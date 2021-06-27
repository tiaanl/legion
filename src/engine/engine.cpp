#include "legion/engine/engine.hpp"

#include <canvas/Windows/window.h>
#include <canvas/app.h>
#include <canvas/message_loop/message_pump_ui.h>
#include <hive/physical_file_locator.h>
#include <nucleus/message_loop/message_loop.h>

namespace le {

// static
Engine* Engine::instance_ = nullptr;

// static
Engine& Engine::instance() {
  DCHECK(instance_) << "Engine has not been initialized.";
  return *instance_;
}

I32 Engine::run() {
  return ca::run<EngineWindowDelegate>(this);
}

bool Engine::initialize(ca::Renderer* renderer) {
  renderer_ = renderer;

  if (!resource_manager_.has_locator()) {
    resource_manager_.set_locator(nu::make_scoped_ref_ptr<hi::PhysicalFileLocator>());
  }

  resource_manager_.set_renderer(renderer);

  return true;
}

}  // namespace le
