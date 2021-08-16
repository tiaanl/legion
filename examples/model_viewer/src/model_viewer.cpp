#include <canvas/app.h>
#include <canvas/renderer/immediate_renderer.h>
#include <floats/transform.h>
#include <hive/locator/physical_file_locator.h>
#include <legion/rendering/rendering.h>
#include <legion/resources/resource_manager.h>

#include <hive/locator/composite_locator.hpp>
#include <legion/engine/engine.hpp>

#if 0
inline fl::Vec2 f(const fl::Pos& p) {
  return {fl::Vec2{static_cast<F32>(p.x), static_cast<F32>(p.y)}};
}

class ModelViewerDelegate : public ca::WindowDelegate {
public:
  ModelViewerDelegate() : ca::WindowDelegate{"legion | Model Viewer"} {}

  bool onWindowCreated(ca::Window* window) override {
    if (!WindowDelegate::onWindowCreated(window)) {
      return false;
    }

#if 0

    auto* renderer = window->getRenderer();

    immediate_renderer_ = nu::makeScopedPtr<ca::ImmediateRenderer>(renderer);

    resource_manager_.setRenderer(renderer);

#if OS(WIN)
    fixtures_locator_.setRootPath(nu::FilePath{R"(C:\Code\silhouette\tests\fixtures)"});
    asteroids_locator_.setRootPath(nu::FilePath{R"(C:\Code\AsteroidDefender\assets)"});
#elif OS(POSIX)
    fixtures_locator_.setRootPath(nu::FilePath{"/home/tilo/code/game/silhouette/tests/fixtures"});
    asteroids_locator_.setRootPath(nu::FilePath{"/home/tilo/code/game/AsteroidDefender/assets"});
#else
#error Unsupported operating system.
#endif

    resource_manager_.add_resource_locator(&fixtures_locator_);
    resource_manager_.add_resource_locator(&asteroids_locator_);

    model_ = resource_manager_.get<le::Model>("box.dae");
    if (!model_) {
      LOG(Error) << "Could not load model.";
      return false;
    }

    add_mouse_event_handler(&camera_controller_);
    add_keyboard_event_handler(&camera_controller_);

#endif  // 0

    return true;
  }

  void onWindowResized(const fl::Size& size) override {
    WindowDelegate::onWindowResized(size);

#if 0
    main_camera_.setAspectRatio(fl::aspect_ratio(size));
#endif  // 0
  }

  void tick(F32 delta) override {
    WindowDelegate::tick(delta);

#if 0
    camera_controller_.tick(delta);
#endif  // 0
  }

  void onRender(ca::Renderer* renderer) override {
#if 0
    renderer->state().depth_test(true);

    // main_camera_.moveTo({0.0f, 2.0f, 10.0f});

    fl::Mat4 projection = fl::Mat4::identity;
    fl::Mat4 view = fl::Mat4::identity;
    main_camera_.updateProjectionMatrix(&projection);
    main_camera_.updateViewMatrix(&view);
    auto mvp = projection * view;

#if 0
    LOG(Info) << "-------------";
    LOG(Info) << mvp.col[0].x << " " << mvp.col[1].x << " " << mvp.col[2].x << " " << mvp.col[3].x;
    LOG(Info) << mvp.col[0].y << " " << mvp.col[1].y << " " << mvp.col[2].y << " " << mvp.col[3].y;
    LOG(Info) << mvp.col[0].z << " " << mvp.col[1].z << " " << mvp.col[2].z << " " << mvp.col[3].z;
    LOG(Info) << mvp.col[0].w << " " << mvp.col[1].w << " " << mvp.col[2].w << " " << mvp.col[3].w;
#endif  // 0

    le::renderModel(renderer, *model_, mvp);

    render_grid(mvp, 1.0f);

    immediate_renderer_->submit_to_renderer();
#endif  // 0
  }

private:
  hi::PhysicalFileLocator fixtures_locator_;
  hi::PhysicalFileLocator asteroids_locator_;
  le::ResourceManager resource_manager_;

  le::Camera main_camera_;
  // le::OrbitCameraController camera_controller_{&main_camera_, fl::Vec3::zero};
  le::FirstPersonCameraController camera_controller_{&main_camera_, 0.1f, 0.08f};
  // le::TopDownCameraController camera_controller_{&main_camera_, {fl::Vec3::up, 0.0f}, 20.0f};

  le::Model* model_ = nullptr;

  nu::ScopedPtr<ca::ImmediateRenderer> immediate_renderer_;
};
#endif  // 0

class ModelViewerLayer : public le::EngineLayer {
public:
  bool on_initialize() override {
    immediate_renderer_ = ca::ImmediateRenderer(&renderer());

#if 0
#if OS(WIN)
    fixtures_locator_.setRootPath(nu::FilePath{R"(C:\Code\silhouette\tests\fixtures)"});
    asteroids_locator_.setRootPath(nu::FilePath{R"(C:\Code\AsteroidDefender\assets)"});
#elif OS(POSIX)
    fixtures_locator_.setRootPath(nu::FilePath{"/home/tilo/code/game/silhouette/tests/fixtures"});
    asteroids_locator_.setRootPath(nu::FilePath{"/home/tilo/code/game/AsteroidDefender/assets"});
#else
#error Unsupported operating system.
#endif

    resource_manager_.add_resource_locator(&fixtures_locator_);
    resource_manager_.add_resource_locator(&asteroids_locator_);
#endif  // 0

    model_ = resource_manager().get_render_model("postbox.obj");
    if (!model_) {
      LOG(Error) << "Could not load model.";
      return false;
    }

    //    add_mouse_event_handler(&camera_controller_);
    //    add_keyboard_event_handler(&camera_controller_);

    return true;
  }

public:
  void on_mouse_moved(const ca::MouseEvent& evt) override {
    if (is_dragging_camera_) {
      camera_horizontal_rotation_ += static_cast<F32>(evt.pos.x - camera_start_drag_.x) * 0.5f;
      camera_vertical_rotation_ += static_cast<F32>(evt.pos.y - camera_start_drag_.y) * 0.5f;
      camera_start_drag_ = evt.pos;
    }
  }

  bool on_mouse_pressed(const ca::MouseEvent& evt) override {
    if (evt.button == ca::MouseEvent::Button::Left) {
      is_dragging_camera_ = true;
      camera_start_drag_ = evt.pos;
    }

    return true;
  }

  void on_mouse_released(const ca::MouseEvent& evt) override {
    if (evt.button == ca::MouseEvent::Button::Left) {
      is_dragging_camera_ = false;
    }
  }

  void on_mouse_wheel(const ca::MouseWheelEvent& evt) override {
    camera_distance_from_origin_ -= static_cast<F32>(evt.wheelOffset.y);
  }

  void on_key_released(const ca::KeyEvent& evt) override {
    if (evt.key == ca::Key::G) {
      show_grid_ = !show_grid_;
    }
  }

  void update(F32 delta) override {}

  void on_render() override {
    renderer().state().depth_test(true);

    auto projection = fl::perspective_projection(
        fl::Angle::fromDegrees(45.0f), fl::aspect_ratio(renderer().size()), 0.01f, 100.0f);

    auto horizontal_rotation =
        fl::rotation_matrix(fl::Vec3::up, fl::Angle::fromDegrees(camera_horizontal_rotation_));
    auto vertical_rotation =
        fl::rotation_matrix(fl::Vec3::right, fl::Angle::fromDegrees(camera_vertical_rotation_));
    auto view = fl::translation_matrix(fl::Vec3::forward * camera_distance_from_origin_) *
                vertical_rotation * horizontal_rotation;

    le::renderModel(&renderer(), *model_, projection * view);

    if (show_grid_) {
      render_grid(projection * view);
      immediate_renderer_->submit_to_renderer();
    }
  }

private:
  void render_grid(const fl::Mat4& transform, F32 size = 1.0f) {
    auto& mesh = immediate_renderer_->create_mesh(ca::DrawType::Lines, transform)
                     .vertex(fl::Vec3::zero)
                     .vertex({100.0f, 100.0f, 100.0f});

    F32 total_size = 10.0f * size;

    for (I32 x = -10; x <= 10; ++x) {
      mesh.vertex({static_cast<F32>(x) * size, 0.0f, -total_size})
          .vertex({static_cast<F32>(x) * size, 0.0f, total_size})
          .vertex({-total_size, 0.0f, static_cast<F32>(x) * size})
          .vertex({total_size, 0.0f, static_cast<F32>(x) * size});
    }
  }

  nu::Optional<ca::ImmediateRenderer> immediate_renderer_;

  le::RenderModel* model_ = nullptr;

  bool is_dragging_camera_ = false;
  F32 camera_horizontal_rotation_ = 0.0f;
  F32 camera_vertical_rotation_ = 0.0f;
  fl::Pos camera_start_drag_;
  F32 camera_distance_from_origin_ = 5.0f;

  bool show_grid_ = true;
};

void set_engine_resource_locator(le::Engine& engine) {
  nu::DynamicArray<nu::ScopedRefPtr<hi::Locator>> locators = {
      nu::make_scoped_ref_ptr<hi::PhysicalFileLocator>(
          nu::FilePath{R"(C:\Code\AsteroidDefender\assets)"}),
      nu::make_scoped_ref_ptr<hi::PhysicalFileLocator>(
          nu::FilePath{R"(C:\Code\silhouette\assets)"}),
      nu::make_scoped_ref_ptr<hi::PhysicalFileLocator>(
          nu::FilePath{R"(C:\Code\silhouette\tests\fixtures)"})};
  engine.resource_manager().set_locator(
      nu::make_scoped_ref_ptr<hi::CompositeLocator>(std::move(locators)));
}

int main() {
  nu::Profiling profiler;
  le::Engine engine;

  set_engine_resource_locator(engine);

  engine.add_layer<ModelViewerLayer>();
  return engine.run();
}
