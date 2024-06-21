#include <Siv3D.hpp>
#include "Settings.hpp"
#include "Window.hpp"
#include "Game.hpp"

using breakout::game::Stage;
using s3d::Size;
using s3d::Vec2;
using s3d::RectF;
using s3d::Circle;
using breakout::game::Ball;
using breakout::game::Paddle;
using breakout::game::Block;

Stage readstageFile(String filename) {
	int index = 0;
	RectF rect;
	Circle circle;
	ColorF color;
	Deserializer<BinaryReader> reader(filename);
	if(not reader) throw Error(U"Failed to open File");
	reader(circle, color, index);
	reader(rect, color, index);
	Stage stage = Stage(Ball(circle, Vec2(0.0, -400.0), color), Paddle(rect.pos.y, rect.size));

	while(1) {
		reader(index);
		if(index == 0) throw Error(std::move(String(U"${file} is have a block whose health is zero").replace(U"${file}", std::move(filename))));
		if(index == 100) break;
		reader(rect, color);
		stage.addBlock(Block(rect, index, color));
	}

	return stage;
}

Array<String> normals = {
	U"stage1.bin",
	U"stage2.bin",
	U"stage3.bin",
	U"stage4.bin",
	U"stage5.bin",
	U"stage6.bin",
	U"stage7.bin",
	U"stage8.bin",
	U"stage9.bin",
	U"stage10.bin",
	U"stage11.bin",
	U"stage12.bin",
	U"stage13.bin",
	U"stage14.bin",
	U"stage15.bin"
};

Array<String> nameds = {
	U"final.bin",
	U"basic1.bin",
	U"basic2.bin",
	U"basic3.bin",
	U"basic4.bin",
	U"crane.bin",
	U"the_two.bin",
	U"the_one.bin"
};

Array<uint32> named_weights = {
	500,
	70,
	130,
	70,
	130,
	50,
	10,
	1
};

void Main() {
	using breakout::game::Game;
	breakout::window::initialize();
	Game game;
	Relocate curtain;
	int stage_num[breakout::settings::game::stage::number_of_stages];
	int32 previous = 0;

	AudioAssetsLoad();
	TextureAssetsLoad();
	FontAssetsLoad();

	while(System::Update()) {
		game.StageCleaner();

		if(breakout::settings::debug) {
			for(String &path : normals) game.addStage(std::move(readstageFile(path)));
			for(String &path : nameds) game.addStage(std::move(readstageFile(path)));
		} else {
			for(int i = 0; i < breakout::settings::game::stage::number_of_stages; i++) {
				if(previous - 1 > i) continue;

				if(previous == 0) {
					if(i == breakout::settings::game::stage::number_of_stages - 1) {
						uint32 sum = 0;
						for(uint32 &weight : named_weights) sum += weight;
						int random = Random(1, (int32)sum);

						for(int j = 0; j < std::size(nameds); j++) {
							random -= named_weights[j];

							if(random <= 0) {
								stage_num[i] = j;
								break;
							}

						}

						if(random > 0) stage_num[i] = 0;
					} else {
						stage_num[i] = Random(0, static_cast<int>(std::size(normals) - 1));
						bool reselect = false;

						for(int j = 0; j < i; j++) if(stage_num[i] == stage_num[j]) {
							reselect = true;
							break;
						}

						if(reselect) {
							i--;
							break;
						}

					}
				}

				if(i == breakout::settings::game::stage::number_of_stages - 1) {
					game.addStage(std::move(readstageFile(nameds[stage_num[i]])));
				} else {
					game.addStage(std::move(readstageFile(normals[stage_num[i]])));
				}

			}
		}

		previous = game.start(previous);
	}


}
