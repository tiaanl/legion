#include <canvas/Renderer/immediate_renderer.h>
#include <canvas/app.h>
#include <floats/transform.h>
#include <hive/physical_file_locator.h>
#include <legion/Rendering/rendering.h>
#include <legion/Resources/resource_manager.h>
#include <nucleus/optional.h>

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
    resource_manager().set_locator(nu::makeScopedRefPtr<hi::PhysicalFileLocator>(
        nu::FilePath{R"(C:\Code\AsteroidDefender\assets)"}));

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

    model_ = resource_manager().get_render_model("enemy.dae");
    if (!model_) {
      LOG(Error) << "Could not load model.";
      return false;
    }

    //    add_mouse_event_handler(&camera_controller_);
    //    add_keyboard_event_handler(&camera_controller_);

    return true;
  }

  void update(F32 delta) override {}

  void on_render() override {
    // fl::Mat4 mvp = fl::Mat4::identity;
    fl::Mat4 mvp = fl::translationMatrix({0.1f, 0.1f, 0.0f});
    le::renderModel(&renderer(), *model_, mvp);

    render_grid(mvp);
    immediate_renderer_->submit_to_renderer();
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
};

int main() {
  nu::Profiling profiler;
  le::Engine engine;
  engine.add_layer<ModelViewerLayer>();
  return engine.run();
}
