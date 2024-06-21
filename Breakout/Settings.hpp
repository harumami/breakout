#pragma once

#define NO_S3D_USING
#include <Siv3D.hpp>

namespace breakout::settings {

	#ifdef _DEBUG
		constexpr bool debug = true;
	#else
		constexpr bool debug = false;
	#endif

	namespace window {
		using s3d::Size;
		constexpr Size size = Size(1920, 1080);
		constexpr bool fullscreen = !debug;
	}

	namespace game {

		namespace effect {
			constexpr double time = 10.0;

			namespace emoji {
				constexpr char32_t strengthening[] = U"💪";
				constexpr char32_t speed_buff[] = U"💊";
				constexpr char32_t speed_buff2[] = U"🚄";
				constexpr char32_t speed_debuff[] = U"🚷";
				constexpr char32_t duplication[] = U"👨‍👨‍👦‍👦";
				constexpr char32_t rain[] = U"⛱";
				constexpr char32_t lightning[] = U"⚡️";
			}

			namespace speed_coefficient {
				constexpr double buff = 1.5;
				constexpr double buff2 = 2.0;
				constexpr double debuff = 0.5;
			}

		}

		namespace paddle {
			using s3d::operator""_degF;
			constexpr float max_reflection_angle = 75_degF;
		}

		namespace item {
			using s3d::RectF;
			constexpr RectF::size_type size = RectF::size_type(30.0, 30.0);
			constexpr double speed = 70.0;
		}

		namespace block {
			using s3d::ColorF;
			constexpr ColorF zero_color = s3d::Palette::Black;
		}

		namespace stage {
			using s3d::uint32;
			constexpr uint32 number_of_stages = 3;
		}

	}

}
