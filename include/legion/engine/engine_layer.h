#pragma once

namespace le {

class ResourceManager;

class EngineLayer : public ca::MouseEventHandlerInterface,
                    public ca::KeyboardEventHandlerInterface {
public:
  virtual ~EngineLayer() = default;

protected:
  ca::Renderer& renderer() {
    return *renderer_;
  }

  le::ResourceManager& resource_manager() {
    return *resource_manager_;
  }

  NU_NO_DISCARD fl::Size size_in_pixels() const {
    return size_;
  }

  virtual bool on_initialize() = 0;
  virtual void update(F32 delta) = 0;
  virtual void on_render() = 0;

  virtual void on_resize(const fl::Size& size) {
    size_ = size;
  }

  void on_mouse_moved(const ca::MouseEvent& evt) override {}

  bool on_mouse_pressed(const ca::MouseEvent& evt) override {
    return false;
  }

  void on_mouse_released(const ca::MouseEvent& evt) override {}

  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override {}

  void on_key_pressed(const ca::KeyEvent& evt) override {}

  void on_key_released(const ca::KeyEvent& evt) override {}

private:
  friend class Engine;
  friend class EngineWindowDelegate;

  ca::Renderer* renderer_ = nullptr;
  le::ResourceManager* resource_manager_ = nullptr;
  fl::Size size_ = {0, 0};
};

}  // namespace le
