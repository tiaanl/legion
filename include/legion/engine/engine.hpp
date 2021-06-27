#pragma once

#include <canvas/Renderer/renderer.h>
#include <nucleus/profiling.h>

#include "engine_window_delegate.h"
#include "legion/Resources/resource_manager.h"

namespace le {

class Engine {
public:
  using LayersType = nu::DynamicArray<nu::ScopedPtr<EngineLayer>>;

  // Return the global singleton instance of the engine.
  static Engine& instance();

  template <typename T, typename... Args>
  void add_layer(Args&&... args) {
    layers_.emplaceBack(nu::make_scoped_ptr<T>(std::forward<Args>(args)...));
  }

  LayersType& layers() {
    return layers_;
  }

  ca::Renderer& renderer() {
    DCHECK(renderer_);
    return *renderer_;
  }

  le::ResourceManager& resource_manager() {
    return resource_manager_;
  }

  // Run the engine main loop.
  I32 run();

private:
  friend EngineWindowDelegate;

  // Called by the EngineWindowDelegate after the window was created and the renderer initialized.
  bool initialize(ca::Renderer* renderer);

  // Pointer to the current singleton Engine instance.
  static Engine* instance_;

  ca::Renderer* renderer_;
  le::ResourceManager resource_manager_;
  LayersType layers_;
};

}  // namespace le
