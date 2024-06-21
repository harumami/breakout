# include <Siv3D.hpp> // OpenSiv3D v0.4.3

class Ball {
public:

	Circle ball;
	ColorF color;

	Ball(Vec2 pos,ColorF color) :ball(pos, 10), color(color) {};

	void draw() {
		ball.draw(color);
	}
	void export_ball(Serializer<BinaryWriter>& writer) {
		writer(ball);
		writer(color);
		writer(100);
	}
	void setpos(Vec2 pos,ColorF Color) {
		ball.center = pos;
		color = Color;
	}
};
class Paddle {
public:

	RectF entity;
	ColorF color;

	Paddle(Vec2 pos, ColorF color) :entity(pos.x ,900,200,20), color(color) {};

	void draw() {
		entity.draw(color);
	}
	void export_paddle(Serializer<BinaryWriter>& writer) {
		writer(entity);
		writer(color);
		writer(100);
	}
	void setpos(Vec2 pos, ColorF Color) {
		entity.pos.x = pos.x ;
		color = Color;
	}
};



class Block {
public:

	RectF block;
	ColorF color;
	int type = 0;

	Block(RectF Block, int type, ColorF Color) :block(Block), type(type), color(Color) {};

	void draw() {
		block.stretched(-1).draw(color).drawFrame(1, 0, Palette::Black);
	}

};

class BlockManager {

	Array<Block> blocks;

public:
	BlockManager() {};

	void add_block(RectF block, int type, ColorF color) {
		blocks << Block(block, type, color);
	}
	void erase_block(Point pos) {
		if (blocks.isEmpty()) return;
		for (auto p = blocks.begin(); p != blocks.end();) {
			if (p->block.contains(pos)) {
				p = blocks.erase(p);
				return;
			}
			else p++;
		}
	}
	void erase_block(RectF scope) {
		if (blocks.isEmpty()) return;
		for (auto p = blocks.begin(); p != blocks.end();) {
			if (scope.contains(p->block)) {
				p = blocks.erase(p);
			}
			else p++;
		}
	}
	void erase_all_block() {
		if (blocks.isEmpty()) return;
		for (auto p = blocks.begin(); p != blocks.end();) {
			p = blocks.erase(p++);
		}
	}
	void add_blocks(RectF block, int type, ColorF color, int32 x_size, int32 y_size) {
		Vec2 Pos = block.pos;
		Vec2 size = block.size;
		int32 x_num = size.x / x_size;
		int32 y_num = size.y / y_size;

		for (auto p : step(x_num)) {
			for (auto q : step(y_num)) {
				add_block(RectF(Pos.x + p * x_size, Pos.y + q * y_size, x_size, y_size), type, color);
			}
		}

	}

	void draw() {
		for (auto p : blocks) p.draw();
	}

	void export_block(Serializer<BinaryWriter> &writer) {

		for (auto p : blocks) {//ファイルに出力する
			if (p.type == 0) {
				Print << U"error";
				continue;
			}
			writer(p.type);
			writer(p.block);
			writer(p.color);

		}
		writer(100);//向こう側での読み込み終了判断
	}

};

class InputM {
public:
	virtual ~InputM() = 0 {};
	virtual void update() = 0;
	virtual bool check() = 0;

};

class ChooseInputM : InputM {
	bool out;
public:
	ChooseInputM() :out(false) {};

	void update() override {
		if (MouseL.down()) out = true;
		else out = false;
	}

	bool check() override {
		return out;
	}


};

class ScopeInputM :InputM {
	bool valid;
	bool out;
	RectF area;
	Point Pos;
public:

	ScopeInputM() :valid(false), out(false) {};

	void update()override {
		if (valid && MouseR.down()) valid = false;
		else if (valid && MouseL.down()) {
			valid = false;
			out = true;
		}
		else if (!valid && MouseL.down()) {
			valid = true;
			area.pos = Cursor::Pos();
		}

		area.size = Vec2(Cursor::PosF() - area.pos);
		if (valid) draw();
	}
	bool check() override {
		return out;
	}
	void draw() {
		area.drawFrame();
	}
	RectF commit() {
		out = false;
		if (area.size.y < 0) {
			area.pos.y = area.pos.y + area.size.y;
			area.size.y = -1 * area.size.y;
		}
		if (area.size.x < 0) {
			area.pos.x = area.pos.x + area.size.x;
			area.size.x = -1 * area.size.x;
		}
		return area;
	}
};
class Image_ {//予約語のせいで変な名前になりました

public:
	RectF area;
	Vec2 pos;
	String pas;
	String name;
	double scale;

	Image_(Point Pos, String Pas, String Name, double Scale) :area(), pos(Pos), pas(Pas), name(Name), scale(Scale) {
		area.size = SizeF((TextureAsset(name).size().x * scale), (TextureAsset(name).size().y * scale));
		area.pos = Vec2(Pos.x - area.size.x / 2, Pos.x - area.size.y / 2);
	};

	void draw() {

		TextureAsset(name).scaled(scale).drawAt(pos);
	}

};

class ImageManager {

	Array<Image_> imgs;

public:


	~ImageManager() {}

	void register_asset(String pas, String name) {

		TextureAsset::Register(name, pas, TextureDesc::Mipped);

	}

	void add_img(Point pos, String pas, String name, double scale) {
		imgs << Image_(pos, pas, name, scale);
	}

	void draw() {
		for (auto p : imgs) {
			p.draw();
		}
	}

	void erase_img(Point pos) {
		if (imgs.isEmpty()) return;
		for (auto p = imgs.begin(); p != imgs.end();) {
			if (p->area.contains(pos)) {
				p = imgs.erase(p);
				return;
			}
			else p++;
		}
	}

	void export_imgs(Serializer<BinaryWriter> &writer) {

		for (auto p : imgs) {
			writer(p.pos);
			writer(p.pas);
			writer(p.name);
			writer(p.scale);
		}

	}
};

class Mode {

public:
	BlockManager blm;
	virtual ~Mode() = 0 {};
	virtual void update() = 0 {};
	virtual void draw() = 0;
};



class CreateMode : Mode {

	String filename;
	String pas;
	String name;
	TextEditState tes1;
	TextEditState tes2;
	TextEditState tes3;
	ScopeInputM ScM;
	ChooseInputM ChM;
	ImageManager IMg;
	Ball ball;
	Paddle paddle;
	const Font font;
	Size size;
	double scale;
	size_t index;
	size_t index2;
	size_t type;
	ColorF color;
	Array<String> toolOption = { U"一個置き",U"範囲置き" ,U"一個消去",U"一括消去",U"画像置き",U"画像消し",U"ボール",U"パドル"};
	Array<String> typeOption = { U"hp１",U"hp２",U"hp３",U"hp４",U"hp５",U"hp６" };
	Array<String> image_name;
	Array<TextureAsset> image;

public:

	CreateMode() :size(41, 21), index(0),index2(0),type(0),pas(U""), name(U""), scale(1.0),
		color(255, 255, 255, 1.0), filename(U"stage.bin"), font(20),ball(Vec2(900,600),color) ,paddle(Vec2(700,900),color){
		ball.setpos(Vec2(900,600), color);
		paddle.setpos(Vec2(Scene::Size().x/2,900), color);

	}

	void update()override {



		if (Cursor::Pos().y > 900 || Cursor::Pos().x > 1920 || index2 == 1) return;
		switch (index) {
		case 0:
			ChM.update();
			if (ChM.check()) {
				blm.add_block(RectF(Cursor::Pos().x - size.x / 2, Cursor::Pos().y - size.y / 2, size), type + 1, color);
			}
			break;
		case 1:
			ScM.update();
			if (ScM.check()) {
				blm.add_blocks(ScM.commit(), type+ 1, color, size.x, size.y);

			}
			break;
		case 2:
			ChM.update();
			if (ChM.check()) {
				blm.erase_block(Cursor::Pos());
			}
			break;
		case 3:
			ScM.update();
			if (ScM.check()) {
				blm.erase_block(ScM.commit());
			}
			break;
		case 4:
			ChM.update();
			if (ChM.check()) {
				IMg.add_img(Cursor::Pos(), pas, name, scale);
			}
			break;
		case 5:
			ChM.update();
			if (ChM.check()) {
				IMg.erase_img(Cursor::Pos());
			}
			break;
		case 6:
			ChM.update();
			if (ChM.check()) {
				ball.setpos(Cursor::Pos(),color);
			}
			break;
		case 7:
			ChM.update();
			Line(Cursor::Pos().x, 0, Cursor::Pos().x, 900).draw(2, Palette::Yellow);
			Line(Cursor::Pos().x+200, 0, Cursor::Pos().x+200, 900).draw(2, Palette::Yellow);
			if (ChM.check()) {
				paddle.setpos(Cursor::Pos(), color);
			}
			break;

		}
	}
	void draw()override {

		IMg.draw();
		blm.draw();
		ball.draw();
		paddle.draw();

		//UI関係するものは全部ここに書いてる
		SimpleGUI::RadioButtons(index2, { U"エディタ",U"設定"}, Vec2(10, 950));

		if (index2) {
			font(U"ファイル名:", filename).draw(650, 10, Palette::Black);
			SimpleGUI::TextBox(tes1, Vec2(650, 40));
			if (SimpleGUI::Button(U"反映する", Vec2(860, 40)))
			{
				filename = tes1.text;
			}
			if (SimpleGUI::Button(U"ファイルを書き出す", Vec2(650, 100)))
			{
				Serializer<BinaryWriter> writer(filename);

				if (!writer) // もしオープンに失敗したら
				{
					throw Error(U"Failed to open `test.bin`");
				}


				ball.export_ball(writer);
				paddle.export_paddle(writer);
				blm.export_block(writer);
				/*
				writer("IMG");
				IMg.export_img(writer);
				*/

			}
			font(U"画像のパス:", pas).draw(650, 210, Palette::Black);
			SimpleGUI::TextBox(tes2, Vec2(650, 240));
			if (SimpleGUI::Button(U"反映する", Vec2(860, 240)))
			{
				pas = tes2.text;
			}
			font(U"画像の名前:", name).draw(650, 310, Palette::Black);
			SimpleGUI::TextBox(tes3, Vec2(650, 340));
			if (SimpleGUI::Button(U"反映する", Vec2(860, 340)))
			{
				name = tes3.text;
			}
			if (SimpleGUI::Button(U"画像を読み込む", Vec2(650, 400)))
			{
				IMg.register_asset(pas, name);
			}


			SimpleGUI::RadioButtons(index, toolOption, Vec2(10, 400));
			SimpleGUI::RadioButtons(type, typeOption, Vec2(150, 400));

			if (SimpleGUI::Button(U"x 大きく", Vec2(600, 500))) size.x += 5;
			if (SimpleGUI::Button(U"x 小さく", Vec2(600, 540))) size.x -= 5;
			if (SimpleGUI::Button(U"y 大きく", Vec2(600, 580))) size.y += 5;
			if (SimpleGUI::Button(U"y 小さく", Vec2(600, 620))) size.y -= 5;
			if (SimpleGUI::Button(U"リセット", Vec2(800, 620), 100)) size = Size(41, 21);
			if (size.x > 101) size.x = 101;
			if (size.y > 101) size.y = 101;
			if (size.x < 0) size.x *= -1;
			if (size.y < 0) size.y *= -1;

			SimpleGUI::Slider(U"R {:.2f}"_fmt(color.r), color.r, Vec2(400, 400), 80, 80);
			SimpleGUI::Slider(U"G {:.2f}"_fmt(color.g), color.g, Vec2(400, 430), 80, 80);
			SimpleGUI::Slider(U"B {:.2f}"_fmt(color.b), color.b, Vec2(400, 460), 80, 80);

			SimpleGUI::Slider(U"画像倍率 {:.2f}"_fmt(scale), scale, Vec2(600, 450), 180, 80);

			Rect(400, 500, size).draw(color).drawFrame(1, 0, Palette::Black);
		}
		else
		{



			Line(0, 900, 1920, 900).draw(2, Palette::Gray);

		}


	}

};



void Main()
{
	CreateMode modec;
	Scene::SetBackground(ColorF(0.9));
	Scene::Resize(1920, 1080);
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetFullscreen(true);

	while (System::Update())
	{	modec.draw();
	modec.update();

	}
}
