#pragma once

#include <Siv3D.hpp>
#include "Settings.hpp"

void AudioAssetsLoad();
void TextureAssetsLoad();
void FontAssetsLoad();

class GUIButton {

	String pas;
	String text;
	String font;
	RectF area;
	Vec2 pos;

public:
	GUIButton(String Name, Vec2 Pos);
	GUIButton(String Name, String font, String Text, Vec2 Pos);

	bool update();


};

//--------------------

class Relocate {
private:
	RectF curtain;
	Transition transition;
	double time;
	double alpha;
	int32 score;
	int32 cleartime;
	bool flag;
public:
	Relocate();
	void receive(int32 score, int32 cleartime);
	void interval(int32 number);
	bool gameover();
	void complete();
	void document();
	void title();
};


//----------------
namespace breakout::game {

	using std::array;
	using s3d::uint32;
	using s3d::Vec2;
	using s3d::Array;
	using s3d::HashTable;
	using s3d::RectF;
	using s3d::Circle;
	using s3d::Texture;
	using s3d::Emoji;
	using s3d::ColorF;

	class Stage;

	class Ball {

	private:
		Circle entity;
		Vec2 velocity;
		ColorF color;
		bool strengthened = false;
		Vec2::value_type speed_coefficient = 1.0;


	public:
		Ball(Circle entity, Vec2 velocity, ColorF color);
		const Circle& getEntity() const;
		const Vec2& getVelocity() const;
		void update(double time);
		void draw() const;
		bool isStrengthened() const;
		void setStrengthened(bool new_strengthened);
		void setSpeedCoefficient(Vec2::value_type new_speed_coefficient);
		void reflect(bool x, bool y);
		void setAngle(Vec2::value_type angle);

	};

	class Effect {

	public:
		static const Effect strengthening;
		static const Effect speed_buff;
		static const Effect speed_buff2;
		static const Effect speed_debuff;
		static const Effect duplication;
		static const Effect rain;
		static const Effect lightning;
		static const array<Effect, 7> effects;

	private:
		uint32 id;
		Emoji emoji;
		Effect(Emoji emoji);

	public:
		const uint32 getID() const;
		const Emoji& getEmoji() const;

	};

	class Item {

	private:
		Effect effect;
		Texture texture;
		RectF entity;

	public:
		Item(Effect effect, Vec2 position);
		const Effect& getEffect() const;
		const Texture& getTexture() const;
		const RectF& getEntity() const;
		void update(double time);
		void draw() const;

	};

	class Block {

	private:
		RectF entity;
		uint32 health;
		uint32 max_health;
		ColorF color;

	public:
		Block(RectF entity, uint32 health, ColorF color);
		const RectF& getEntity() const;
		const ColorF& getColor() const;
		void draw() const;
		bool damage();
		Item getItem() const;

	};

	class Paddle {

	private:
		RectF entity;
		array<double, std::size(Effect::effects)> effects;
		s3d::Effect render_effect;

	public:
		Paddle(RectF::position_type::value_type y, RectF::size_type size);
		const RectF& getEntity() const;
		void update(double time, Ball& ball);
		void draw() const;
		void addEffect(Effect effect, Ball &ball, Array<Block>& blocks);
		void clearRenderEffects();

	};

	enum class StageResult {
		Clear,
		Failed,
		Going
	};

	class Stage {

	private:
		Ball ball;
		Paddle paddle;
		Array<Block> blocks;
		Array<Item> items;
		s3d::Effect effect;
		Stopwatch timer;
		int32 t_time;
	public:
		Stage(Ball ball, Paddle paddle);
		void addBlock(Block block);
		bool start(int32& score, int32& time);

	private:
		StageResult update(int32& score);

	};

	class Game {

	private:
		Array<Stage> stages;
		Relocate curtain;

	public:
		int32 score;
		int32 time;
		void addStage(Stage stage);
		int32 start(int32 num);//0:最初から,1:1から,...
		void StageCleaner();
	};

}
