#include "Game.hpp"
#include "Settings.hpp"


void AudioAssetsLoad() {
	AudioAsset::Register(U"rainy", U"rainy.mp3");
	AudioAsset::Load(U"rainy");
	//---------
	AudioAsset::Register(U"lightning", U"lightning.mp3");
	AudioAsset::Load(U"lightning");
	//---------
	AudioAsset::Register(U"explosion", U"explosion2.mp3");
	AudioAsset::Load(U"explosion");
	//----------
	AudioAsset::Register(U"crush1", U"blockcrush.mp3");
	AudioAsset::Load(U"crush1");
	AudioAsset::Register(U"crush2", U"blockcrush2.mp3");
	AudioAsset::Load(U"crush2");
	AudioAsset::Register(U"crush3", U"blockcrush3.mp3");
	AudioAsset::Load(U"crush3");
	AudioAsset::Register(U"crush4", U"blockcrush4.mp3");
	AudioAsset::Load(U"crush4");
	//----------
	AudioAsset::Register(U"speedup", U"speedup.mp3");
	AudioAsset::Load(U"speedup");
	AudioAsset::Register(U"speeddown", U"speeddown.mp3");
	AudioAsset::Load(U"speeddown");
	AudioAsset::Register(U"powerup", U"powerup.mp3");
	AudioAsset::Load(U"powerup");
	//-----------
	AudioAsset::Register(U"bump", U"flying_pan.mp3");
	AudioAsset::Load(U"bump");
	AudioAsset::Register(U"woodbump", U"woodbump.mp3");
	AudioAsset::Load(U"woodbump");
	//------------------
	AudioAsset::Register(U"Title", U"wind.mp3", Loop::Yes);
	AudioAsset::Load(U"Title");
	AudioAsset::Register(U"Bad", U"moonlight.mp3", Loop::Yes);
	AudioAsset::Load(U"Bad");
	AudioAsset::Register(U"Scene", U"horabgm.mp3", Loop::Yes);
	AudioAsset::Load(U"Scene");
	AudioAsset::Register(U"End", U"star.mp3", Loop::Yes);
	AudioAsset::Load(U"End");
}

void TextureAssetsLoad() {
	TextureAsset::Register(U"redo", 0xF17A8_icon, 300);
	TextureAsset::Load(U"redo");
	//--------------------------
	TextureAsset::Register(U"home", 0xF0BA7_icon, 300);
	TextureAsset::Load(U"home");
	//--------------------------
	TextureAsset::Register(U"retry", 0xF17B4_icon, 300);
	TextureAsset::Load(U"retry");
	//--------------------------
	TextureAsset::Register(U"exit", 0xF0A48_icon, 300);
	TextureAsset::Load(U"exit");
	//--------------------------
	TextureAsset::Register(U"gear", 0xF0E61_icon, 300);
	TextureAsset::Load(U"gear");
	//--------------------------
	TextureAsset::Register(U"start", 0xF141C_icon, 300);
	TextureAsset::Load(U"start");
	//--------------------------
	TextureAsset::Register(U"play", 0xF127A_icon, 300);
	TextureAsset::Load(U"play");
	//--------------------------
	TextureAsset::Register(U"exit", 0xF0E61_icon, 300);
	TextureAsset::Load(U"exit");
	//--------------------------
	TextureAsset::Register(U"school", 0xF0474_icon, 300);
	TextureAsset::Load(U"school");
	//--------------------------
	TextureAsset::Register(U"lightning", U"lightning.png", TextureDesc::Mipped);
	TextureAsset::Load(U"lightning");
	//--------------------------
	TextureAsset::Register(U"bump", U"bump.png");
	TextureAsset::Load(U"bump");
	TextureAsset::Register(U"explosion", U"explosion.png");
	TextureAsset::Load(U"explosion");
	//--------------------------
	TextureAsset::Register(U"speedup", U"speedup.png");
	TextureAsset::Load(U"speedup");
	//--------------------------
	TextureAsset::Register(U"speeddown", U"speeddown.png");
	TextureAsset::Load(U"speeddown");
	//--------------------------
	TextureAsset::Register(U"powerup", U"powerup.png");
	TextureAsset::Load(U"powerup");
	//----------------------------
	TextureAsset::Register(U"Title", U"Title.jpg");
	TextureAsset::Load(U"Title");
	//----------------------------
	TextureAsset::Register(U"Title2", U"Title2.png");
	TextureAsset::Load(U"Title2");
	TextureAsset::Register(U"Scene", U"stage.jpg");
	TextureAsset::Load(U"Scene");
	//----------------------------
	TextureAsset::Register(U"END", U"happyend.jpg");
	TextureAsset::Load(U"END");
	//----------------------------
	TextureAsset::Register(U"Crack", U"hibi2.png");
	TextureAsset::Load(U"Crack");
	TextureAsset::Register(U"Block_Material", U"hibi.png");
	TextureAsset::Load(U"Block_Material");
	TextureAsset::Register(U"Block_Material2", U"buroteku.jpg");
	TextureAsset::Load(U"Block_Material2");
}

void FontAssetsLoad() {
	FontAsset::Register(U"Title", FontMethod::SDF, 250, U"togalite/Togalite-Medium.otf");
	FontAsset::Load(U"Title");
	FontAsset::Register(U"Title_f", 250, U"togalite/Togalite-Medium.otf");
	FontAsset::Load(U"Title_f");
	//--------------------------
	FontAsset::Register(U"Medium", 120, U"togalite/Togalite-Medium.otf");
	FontAsset::Load(U"Medium");
	//--------------------------
	FontAsset::Register(U"Medium_mini", 100, U"togalite/Togalite-Medium.otf");
	FontAsset::Load(U"Medium_mini");
	//--------------------------
	FontAsset::Register(U"Heavy", 120, U"togalite/Togalite-Heavy.otf");
	FontAsset::Load(U"Heavy");
	//--------------------------
	FontAsset::Register(U"Heavy_mini", 60, U"togalite/Togalite-Heavy.otf");
	FontAsset::Load(U"Heavy_mini");
	//--------------------------
	FontAsset::Register(U"Titlets", 250, U"Rex/Rex/Commercial/OTF/Rex-BoldInline.otf");
	FontAsset::Load(U"Titlets");
	//--------------------------
	FontAsset::Register(U"Medium40", 40, U"togalite/Togalite-Medium.otf");
	FontAsset::Load(U"Medium40");
}
//-----------
//-------------------------
struct Particle
{
	Vec2 start;
	Vec2 velocity;
};
//-------Effect------------
struct Buffpower :IEffect {

	double cut_x;
	double cut_y;
	double now_x;
	double now_y;
	double scale;
	Vec2 pos;
	const Texture anim;
	const Audio audio;


	Buffpower(const Vec2& Pos) :anim(TextureAsset(U"powerup"))
		, audio(AudioAsset(U"powerup")), pos(Pos), now_x(0), now_y(0), scale(0.3) {
		cut_x = anim.size().x / 5;
		cut_y = anim.size().y / 6;
		pos.x -= (int)cut_x * scale / 2;
		pos.y -= (int)cut_y * scale / 2;
		audio.play();
	};

	~Buffpower() {};

	bool update(double t) override
	{
		draw();

		now_x += cut_x;
		if (now_x >= anim.size().x) {
			now_x = 0;
			now_y += cut_y;
		}
		if (now_y >= anim.size().y) return false;
		return t < 1.0;
	};

	void draw() {
		anim(now_x, now_y, cut_x, cut_y).scaled(scale).draw(pos);
	};
};

struct Buffdown :IEffect {

	double cut_x;
	double cut_y;
	double now_x;
	double now_y;
	double scale;
	Vec2 pos;
	const Texture anim;
	const Audio audio;


	Buffdown(const Vec2& Pos) :anim(TextureAsset(U"speeddown"))
		, audio(AudioAsset(U"speeddown")), pos(Pos), now_x(0), now_y(0), scale(0.3) {
		cut_x = anim.size().x / 5;
		cut_y = anim.size().y / 6;
		pos.x -= (int)cut_x * scale / 2;
		pos.y -= (int)cut_y * scale / 2;
		audio.play();
	};

	~Buffdown() {};

	bool update(double t) override
	{
		draw();

		now_x += cut_x;
		if (now_x >= anim.size().x) {
			now_x = 0;
			now_y += cut_y;
		}
		if (now_y >= anim.size().y) return false;
		return t < 1.0;
	};

	void draw() {
		anim(now_x, now_y, cut_x, cut_y).scaled(scale).draw(pos);
	};
};

struct Buffspeed :IEffect {

	double cut_x;
	double cut_y;
	double now_x;
	double now_y;
	double scale;
	Vec2 pos;
	const Texture anim;
	const Audio audio;


	Buffspeed(const Vec2& Pos) :anim(TextureAsset(U"speedup"))
		, audio(AudioAsset(U"speedup")), pos(Pos), now_x(0), now_y(0), scale(0.3) {
		cut_x = anim.size().x / 5;
		cut_y = anim.size().y / 6;
		pos.x -= (int)cut_x * scale / 2;
		pos.y -= (int)cut_y * scale / 2;
		audio.play();
	};

	~Buffspeed() {};

	bool update(double t) override
	{
		draw();

		now_x += cut_x;
		if (now_x >= anim.size().x) {
			now_x = 0;
			now_y += cut_y;
		}
		if (now_y >= anim.size().y) return false;
		return t < 1.0;
	};

	void draw() {
		anim(now_x, now_y, cut_x, cut_y).scaled(scale).draw(pos);
	};
};

struct Rain : IEffect
{
	Array<Particle> points;

	Rain() {
		AudioAsset(U"rainy").play();
	}
	~Rain() {
		AudioAsset(U"rainy").stop(5s);
	}
	bool update(double t) override {

		if (RandomBool()) {
			for (int i = 0; i < 3; i++)points << Particle(Vec2(Random(0, Scene::Size().x), 0), Vec2(0, 10));
		}

		for (auto& p : points) {
			Circle(p.start, 2).draw(Palette::Blue);
			p.start.y = p.start.y + p.velocity.y;
		}
		

		return t <= 10.0;
	}

};

struct Lightning : IEffect {
	double cut_x;
	double cut_y;
	double now_x;
	double now_y;
	double scale;
	Vec2 pos;
	const Texture anim;

	Lightning(const RectF& paddle, Array<breakout::game::Block>& blocks) :anim(TextureAsset(U"lightning")), pos(paddle.center()), now_x(0), now_y(0)
		, scale(5.0) {
		cut_x = anim.size().x / 7;
		cut_y = anim.size().y / 9;
		pos.x -= (int)cut_x * scale / 2;
		pos.y = -140;
		AudioAsset(U"lightning").playOneShot();

		blocks.remove_if([&](breakout::game::Block block) {
			return (paddle.x < block.getEntity().pos.x&& block.getEntity().pos.x < paddle.rightCenter().x) || (paddle.x < block.getEntity().rightCenter().x&& block.getEntity().rightCenter().x < paddle.rightCenter().x);
		});

	}
	~Lightning() {};

	bool update(double t) override
	{
		draw();

		now_x += cut_x;
		if (now_x >= anim.size().x) {
			now_x = 0;
			now_y += cut_y;
		}
		if (now_y >= anim.size().y) return false;
		return t < 1.0;
	}

	void draw() {
		anim(now_x, now_y, cut_x, cut_y).scaled(scale).draw(pos);
	}
};

struct Crush : IEffect
{

	Crush(int32 type)
	{
		switch (type) {
		case 0: AudioAsset(U"crush1").play();
			break;
		case 1: AudioAsset(U"crush2").play();
			break;
		case 2: AudioAsset(U"crush3").play();
			break;
		case 3: AudioAsset(U"crush4").play();
			break;
		}
	}

	bool update(double t) override {
		return t < 1.0;
	}
};


struct notDestroyCrush :IEffect {

	double cut_x;
	double cut_y;
	double now_x;
	double now_y;
	double scale;
	Vec2 pos;
	const Texture anim;
	const Audio audio;


	notDestroyCrush(const Vec2& Pos) :anim(TextureAsset(U"bump"))
		, audio(AudioAsset(U"bump")), pos(Pos), now_x(0), now_y(0), scale(0.3) {
		cut_x = anim.size().x / 5;
		cut_y = anim.size().y / 6;
		pos.x -= (int)cut_x * scale / 2;
		pos.y -= (int)cut_y * scale / 2;
		audio.playOneShot();
	};

	

	bool update(double t) override
	{
		draw();

		now_x += cut_x;
		if (now_x >= anim.size().x) {
			now_x = 0;
			now_y += cut_y;
		}
		if (now_y >= anim.size().y) return false;
		return t < 1.0;
	};

	void draw() {
		anim(now_x, now_y, cut_x, cut_y).scaled(scale).draw(pos);
	};
};


struct Spark : IEffect
{
	Array<Particle> m_particles;
	ColorF color;
	Crush audio;


	Spark(const Vec2& start, ColorF color) : m_particles(100), color(color), audio(Random(0, 3))
	{
		for (auto& particle : m_particles)
		{
			particle.start = start + RandomVec2(20.0);
			particle.velocity = RandomVec2(1.0) * Random(80.0);
		}
	}

	bool update(double t) override
	{
		for (const auto& particle : m_particles)
		{
			const Vec2 pos = particle.start
				+ particle.velocity * t + 0.5 * t * t * Vec2(0, 240);

			Triangle(pos, 16.0, pos.x * 5_deg).draw(HSV(color).toColorF(1.0 - t));
		}

		return t < 1.0;
	}
};

struct Explosion :IEffect {

	double cut_x;
	double cut_y;
	double now_x;
	double now_y;
	Vec2 pos;
	const Texture anim;
	const Audio audio;


	Explosion(const Vec2& Pos) :anim(TextureAsset(U"explosion"))
		, audio(AudioAsset(U"explosion")), pos(Pos), now_x(0), now_y(0) {
		cut_x = anim.size().x / 7;
		cut_y = anim.size().y / 9;
		pos.x -= (int)cut_x / 2;
		pos.y -= (int)cut_y / 2;
		audio.play();
	};

	~Explosion() {};

	bool update(double t) override
	{
		draw();

		now_x += cut_x;
		if (now_x >= anim.size().x) {
			now_x = 0;
			now_y += cut_y;
		}
		if (now_y >= anim.size().y) return false;
		return t < 1.0;
	}

	void draw() {
		anim(now_x, now_y, cut_x, cut_y).draw(pos);
	}
};

struct Bump :IEffect
{

	Bump() {
		AudioAsset(U"woodbump").playOneShot();
	}
	bool update(double t) override
	{
		return t < 1.0;
	}
};



//-----------

GUIButton::GUIButton(String Name, Vec2 Pos) :pas(Name), font(U""), text(U""), pos(Pos), area(Pos - TextureAsset(Name).size() / 2, TextureAsset(Name).size()) {
};
GUIButton::GUIButton(String Name, String Font, String Text, Vec2 Pos) :pas(Name), font(Font), text(Text), pos(Pos), area(Pos - TextureAsset(Name).size() / 2, TextureAsset(Name).size()) {
};

bool GUIButton::update() {

	if (area.mouseOver()) {
		TextureAsset(pas).resized(TextureAsset(pas).size() * 1.2).drawAt(pos);
		if (area.leftClicked()) return true;
		FontAsset(font)(text).drawAt(pos.x, pos.y - 200, ColorF(140, 0.7));
	}
	else TextureAsset(pas).drawAt(pos);
	return false;
};



//-----------------------------

Relocate::Relocate() :curtain(RectF(0, 0, Scene::Size())), time(0), alpha(1.0)
, transition(2.5s, 2.5s), score(0), cleartime(0), flag(false) {}

void Relocate::receive(int32 Score, int32 Time) {

	score += Score;
	cleartime += Time;

}

void Relocate::interval(int32 number) {
	time = 0;

	while (System::Update()) {
		time += Scene::DeltaTime();
		transition.update(time < 2.0);
		curtain.draw(ColorF(0, 0, 0, transition.value()));
		FontAsset(U"Title")(U"Stage", number).drawAt(Scene::Center().x, 300, ColorF(255, transition.value()));
		if (time > 5.0) break;
	}
	
}

bool Relocate::gameover() {
	AudioAsset(U"Bad").play(2s);
	time = 0;

	while (System::Update()) {
		time += Scene::DeltaTime();
		transition.update(time < 98.0);
		TextureAsset(U"Title2").drawAt(Scene::Center(), ColorF(transition.value()));
		FontAsset(U"Title")(U"Continue?").drawAt(Scene::Center().x, 300, ColorF(Palette::Red, transition.value()));
		FontAsset(U"Midium")(U"    score: ", score).drawAt(600, 600, ColorF(Palette::Red, transition.value()));
		FontAsset(U"Midium")(U"clear time: ", cleartime / 60, U"min", cleartime % 60, U"sec").drawAt(600, 700, ColorF(Palette::Red, transition.value()));

		if(time > 1.5) {
			if (GUIButton(U"redo", U"Medium_mini", U"最初から", Vec2(500, 800)).update()) {
				flag = true;
				AudioAsset(U"Bad").stop(2s);
				return false;
			}
			if (GUIButton(U"retry", U"Medium_mini", U"リトライ", Vec2(1000, 800)).update()) {
				flag = true;
				AudioAsset(U"Bad").stop(2s);
				return true;
			}
			if (GUIButton(U"home", U"Medium_mini", U"タイトルに戻る", Vec2(1500, 800)).update()) {
				cleartime = 0;
				AudioAsset(U"Bad").stop(2s);
				break;
			}
		}

		if (time > 100.0)break;
	}

	flag = false;//タイトル無視フラグ
	score = 0;
	return false;
}

void Relocate::complete() {
	time = 0;

	while (System::Update()) {
		time += Scene::DeltaTime();
		if (time > 2.0) AudioAsset(U"End").play(5s);
		transition.update(time > 0.5);
		TextureAsset(U"END").drawAt(Scene::Center(), ColorF(transition.value()));
		RectF(0, 500, Scene::Size().x, Scene::Size().y - 650).draw(ColorF(0, 0.1));
		FontAsset(U"Titlets")(U"GAME CLEAR!!").drawAt(Scene::Center().x, 310, HSV(ColorF(Palette::Yellow, transition.value())));
		FontAsset(U"Heavy")(U"     score:", score).drawAt(700, 700, HSV(ColorF(255, 145, 144, transition.value())));
		FontAsset(U"Heavy")(U"clear time:", cleartime / 60, U"min", cleartime % 60, U"sec").drawAt(700, 900, HSV(ColorF(255, 145, 144, transition.value())));

		if (time > 1.5) {
			if (GUIButton(U"home", U"Medium_mini", U"タイトルに戻る", Vec2(1550, 800)).update()) {
				cleartime = 0;
				time = 0;
				score = 0;
				AudioAsset(U"End").stop(2s);
				flag = false;
				return;
			}
		}
	}
}

void Relocate::document() {
	const Texture strength{ Emoji(breakout::settings::game::effect::emoji::strengthening) };
	const Texture speed_buff{ Emoji(breakout::settings::game::effect::emoji::speed_buff) };
	const Texture speed_buff2{ Emoji(breakout::settings::game::effect::emoji::speed_buff2) };
	const Texture speed_debuff{ Emoji(breakout::settings::game::effect::emoji::speed_debuff) };
	const Texture rain{ Emoji(breakout::settings::game::effect::emoji::rain) };
	const Texture lightning{ Emoji(breakout::settings::game::effect::emoji::lightning) };

	while(System::Update()) {
		TextureAsset(U"Title").drawAt(Scene::Center());
		RectF(0, 0, Scene::Size()).draw(ColorF(0, 0.3));

		FontAsset(U"Heavy")(U"アイテム説明").drawAt(Scene::Center().x, 100);

		
		strength.drawAt(165, 300);
		GUIButton(U"school", U"Medium40", U"                                               ボールがブロックを貫通するようになります", Vec2(165, 600)).update();
		speed_buff.drawAt(495, 300);
		GUIButton(U"school", U"Medium40", U"ボールの速度が上がります", Vec2(495, 600)).update();
		speed_buff2.drawAt(825, 300);
		GUIButton(U"school", U"Medium40", U"ボールの速度が超上がります", Vec2(825, 600)).update();
		speed_debuff.drawAt(1155, 300);
		GUIButton(U"school", U"Medium40", U"ボールの速度が下がります", Vec2(1155, 600)).update();
		rain.drawAt(1485, 300);
		GUIButton(U"school", U"Medium40", U"雨が降ります", Vec2(1485, 600)).update();
		lightning.drawAt(1815, 300);
		GUIButton(U"school", U"Medium40", U"落雷注意！！", Vec2(1815, 600)).update();

		if (GUIButton(U"redo", U"Heavy_mini", U"戻る", Vec2(Scene::Center().x + 700, 900)).update()) return;

	}

}

void Relocate::title() {
	if (flag)return;
	AudioAsset(U"Title").play(2s);
	time = 0;

	while (System::Update()) {
		time += Scene::DeltaTime();
		transition.update(time > 1.0);
		TextureAsset(U"Title").drawAt(Scene::Center(), ColorF(transition.value()));
		FontAsset(U"Heavy_mini")(breakout::settings::debug ? U"Debug" : U"    ようこそ    ").drawAt(Scene::Center().x, 100, ColorF(255, transition.value()));
		FontAsset(U"Title")(U"ブロック崩し").drawAt(Scene::Center().x + 5, 305, ColorF(0, transition.value()));
		FontAsset(U"Title")(U"ブロック崩し").drawAt(Scene::Center().x, 300, ColorF(255, transition.value()));

		if (time > 1.5) {
			if (GUIButton(U"start", U"Medium_mini", U"ブロックを崩しに行く?", Vec2(Scene::Center().x, 800)).update()) {
				AudioAsset(U"Title").stop(2s);
				break;
			}
			if (GUIButton(U"school", U"Medium_mini", U"予習", Vec2(Scene::Center().x + 700, 900)).update()) {
				document();
			}
		}

	}

	score = 0;

}

namespace breakout::game {
	Ball::Ball(Circle entity, Vec2 velocity, ColorF color) : entity(entity), velocity(velocity), color(color) {}

	const Circle& Ball::getEntity() const {
		return entity;
	}

	const Vec2& Ball::getVelocity() const {
		return velocity;
	}

	void Ball::update(double time) {
		entity.x += time * speed_coefficient * velocity.x;
		entity.y += time * speed_coefficient * velocity.y;

	}

	void Ball::draw() const {
		entity.draw(color);
	}

	bool Ball::isStrengthened() const {
		return strengthened;
	}

	void Ball::setStrengthened(bool new_strengthened) {

		strengthened = new_strengthened;
	}

	void Ball::setSpeedCoefficient(Vec2::value_type new_speed_coefficient) {

		speed_coefficient = new_speed_coefficient;
	}

	void Ball::reflect(bool x, bool y) {
		if (x) velocity.x *= -1;
		if (y) velocity.y *= -1;
	}

	void Ball::setAngle(Vec2::value_type angle) {
		Vec2::value_type length = velocity.length();
		velocity = Vec2(length * std::cos(angle), length * std::sin(angle));
	}

	const Effect Effect::strengthening = Effect(Emoji(settings::game::effect::emoji::strengthening));
	const Effect Effect::speed_buff = Effect(Emoji(settings::game::effect::emoji::speed_buff));
	const Effect Effect::speed_buff2 = Effect(Emoji(settings::game::effect::emoji::speed_buff2));
	const Effect Effect::speed_debuff = Effect(Emoji(settings::game::effect::emoji::speed_debuff));
	const Effect Effect::duplication = Effect(Emoji(settings::game::effect::emoji::duplication));
	const Effect Effect::rain = Effect(Emoji(settings::game::effect::emoji::rain));
	const Effect Effect::lightning = Effect(Emoji(settings::game::effect::emoji::lightning));

	const array<Effect, 7> Effect::effects = {
		strengthening,
		speed_buff,
		speed_buff2,
		speed_debuff,
		duplication,
		rain,
		lightning
	};

	Effect::Effect(Emoji emoji) : emoji(emoji) {
		static uint32 nextID = 0;
		id = nextID++;
	}

	const uint32 Effect::getID() const {
		return id;
	}

	const Emoji& Effect::getEmoji() const {
		return emoji;
	}

	Paddle::Paddle(RectF::position_type::value_type y, RectF::size_type size) : entity(RectF(0, y, size)), effects(array<double, std::size(Effect::effects)>()) {}

	const RectF& Paddle::getEntity() const {
		return entity;
	}

	void Paddle::update(double time, Ball& ball) {
		entity.setCenter(s3d::Cursor::Pos().x, entity.center().y);
		for (auto& effect : effects) if (effect > 0) effect -= std::min(effect, time);
		ball.setStrengthened(effects[Effect::strengthening.getID()] > 0.0);
		double speedCoefficient = 1.0;
		if (effects[Effect::speed_buff.getID()] > 0.0) {
			speedCoefficient *= settings::game::effect::speed_coefficient::buff;
		}
		if (effects[Effect::speed_buff2.getID()] > 0.0) {
			speedCoefficient *= settings::game::effect::speed_coefficient::buff2;
		}
		if (effects[Effect::speed_debuff.getID()] > 0.0) {
			speedCoefficient *= settings::game::effect::speed_coefficient::debuff;
		}
		ball.setSpeedCoefficient(speedCoefficient);
	}

	void Paddle::draw() const {
		entity.draw();
		render_effect.update();
	}

	void Paddle::addEffect(Effect effect, Ball& ball, Array<Block>& blocks) {
		effects[effect.getID()] = settings::game::effect::time;
		if (effect.getID() == Effect::rain.getID()) render_effect.add<Rain>();
		if (effect.getID() == Effect::lightning.getID()) render_effect.add<Lightning>(entity, blocks);
		if (effect.getID() == Effect::speed_buff.getID()) render_effect.add<Buffspeed>(ball.getEntity().center);
		if (effect.getID() == Effect::speed_buff2.getID()) render_effect.add<Buffspeed>(ball.getEntity().center);
		if (effect.getID() == Effect::speed_debuff.getID()) render_effect.add<Buffdown>(ball.getEntity().center);
		if (effect.getID() == Effect::strengthening.getID()) render_effect.add<Buffpower>(ball.getEntity().center);
	}

	void Paddle::clearRenderEffects() {
		render_effect.clear();
	}

	Item::Item(Effect effect, Vec2 position) : effect(effect), texture(Texture(effect.getEmoji())), entity(RectF(position, settings::game::item::size)) {}

	const Effect& Item::getEffect() const {
		return effect;
	}

	const Texture& Item::getTexture() const {
		return texture;
	}

	const RectF& Item::getEntity() const {
		return entity;
	}

	void Item::update(double time) {
		entity.y += settings::game::item::speed * time;
	}

	void Item::draw() const {
		texture.resized(entity.size).drawAt(entity.pos);
	}

	Block::Block(RectF entity, uint32 health, ColorF color) : entity(entity), health(health), max_health(health), color(color) {}

	const RectF& Block::getEntity() const {
		return entity;
	}

	const ColorF& Block::getColor() const {
		return color;
	}

	void Block::draw() const {
		double rate = (double)health / (double)max_health;
		entity.draw(rate * color + (1.0 - rate) * settings::game::block::zero_color).drawFrame(3.0, 0.0, s3d::Palette::Black);
		Random(0, 1) ? TextureAsset(U"Block_Material").resized(entity.size).draw(entity.pos, ColorF(255, 0.3)) : TextureAsset(U"Block_Material2").resized(entity.size).draw(entity.pos, ColorF(255, 0.3));
		TextureAsset(U"Crack").resized(entity.size).draw(entity.pos, ColorF(255, 1 - rate));
	}

	bool Block::damage() {
		return --health == 0;
	}

	Item Block::getItem() const {
		using s3d::Random;
		Effect effect = Effect::effects[Random(std::size(Effect::effects) - 2)];
		if(effect.getID() == Effect::duplication.getID()) effect = Effect::effects[std::size(Effect::effects) - 1];
		return Item(effect, entity.center());
	}

	Stage::Stage(Ball ball, Paddle paddle) : ball(ball), paddle(paddle) {}

	void Stage::addBlock(Block block) {
		blocks << block;
	}

	bool Stage::start(int32& score, int32& Time) {
		timer.restart();
		AudioAsset(U"Scene").play(1s);

		while (s3d::System::Update()) {
			double time = s3d::Scene::DeltaTime();
			ball.update(time);
			paddle.update(time, ball);
			for (auto& item : items) item.update(time);
			StageResult result = this->update(score);
			TextureAsset(U"Scene").drawAt(Scene::Center());
			ball.draw();
			paddle.draw();
			for (auto& block : blocks) block.draw();
			for (auto& item : items) item.draw();
			effect.update();

			if(result == StageResult::Clear || result == StageResult::Failed) {
				paddle.clearRenderEffects();
				effect.clear();
				Time = timer.s();
				AudioAsset(U"Scene").stop(2s);
				return result == StageResult::Clear;
			}
			
		}

		return false;
	}

	StageResult Stage::update(int32& score) {
		using s3d::operator""_degF;

		for (auto it = items.begin(); it != items.end(); it++) if (paddle.getEntity().intersects(it->getEntity())) {
			paddle.addEffect(it->getEffect(), ball, blocks);
			items.erase(it);
			break;
		}
		else if (it->getEntity().y > s3d::Scene::Height()) {
			items.erase(it);
			break;
		}

		if (blocks.isEmpty()) {
			return StageResult::Clear;
		}
		else if ((ball.getEntity().x < 0.0 && ball.getVelocity().x < 0.0) || (ball.getEntity().x > s3d::Scene::Width() && ball.getVelocity().x > 0.0)) {
			ball.reflect(true, false);
			effect.add<Bump>();
			return StageResult::Going;
		}
		else if (ball.getEntity().y < 0.0 && ball.getVelocity().y < 0.0) {
			ball.reflect(false, true);
			effect.add<Bump>();
			return StageResult::Going;
		}
		else if (ball.getEntity().y > s3d::Scene::Height() && ball.getVelocity().y > 0.0) {
			return StageResult::Failed;
		}
		else if (ball.getEntity().intersects(paddle.getEntity())) {
			ball.setAngle(settings::game::paddle::max_reflection_angle * (2.0 * (ball.getEntity().x - paddle.getEntity().x) / paddle.getEntity().w - 1.0) - 90_degF);
			return StageResult::Going;
		}
		else {

			for (auto it = blocks.begin(); it != blocks.end(); it++) if (ball.getEntity().intersects(it->getEntity())) {
				if (!ball.isStrengthened()) ball.reflect(ball.getEntity().intersects(it->getEntity().left()) || ball.getEntity().intersects(it->getEntity().right()), ball.getEntity().intersects(it->getEntity().top()) || ball.getEntity().intersects(it->getEntity().bottom()));
				
				if (it->damage()) {
					effect.add<Spark>(it->getEntity().center(), it->getColor());
					if (t_time == 0) {
						t_time = 10;
						score += 10;
					}
					else {
						score += 10 * t_time;
					}

					items << it->getItem();
					blocks.erase(it);
				}
				 else effect.add<notDestroyCrush>(ball.getEntity().center);

				break;
			}

			if (t_time != 0) {
				t_time--;
			}

			return StageResult::Going;
		}

	}

	void Game::addStage(Stage stage) {
		stages << std::move(stage);
	}

	int32 Game::start(int32 num) {
		int32 i = num ? num : 1;
		curtain.title();

		for (auto& stage : stages) {
			curtain.interval(i);

			if (!(stage.start(score, time) || settings::debug)) {
				curtain.receive(0, time);
				if(curtain.gameover()) return i;//curtain.gameover()がtrue→Retry
				else return 0;
			}

			curtain.receive(score, time);
			i++;
		}

		curtain.complete();
		return 0;
	}


	void Game::StageCleaner() {
		if (stages) {
			stages.clear();
		}
	}
}
