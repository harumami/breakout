#include "Window.hpp"
#include <Siv3D.hpp>
#include "Settings.hpp"

namespace breakout::window {
	void initialize() {
		using s3d::ResizeMode;

		s3d::Scene::Resize(settings::window::size);
		s3d::Scene::SetResizeMode(ResizeMode::Keep);
		s3d::Window::SetFullscreen(settings::window::fullscreen);

	}
}
