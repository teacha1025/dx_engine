#if 0
#include "dx_engine.h"

namespace dx_engine {

}

using namespace dx_engine;

define N = 60.0;

void init() {
	dx_engine::log.set(true, false);
	//window.fullscreen(true, fullscreen_type::borderless_dotbydot);
	window.size({ 1280,960 });
	window.background(pallet::lightskyblue);
	window.title("TEST");
	window.extends(systems.monitor_size().x / 1920.0);
	//file.load("resource.dat");

	//systems.vsync(false);
	//systems.max_fps(N);
}
#if 0
#define KEY systems.keyboard
class testscene : public scene<> {
private:
	uint counter = 0;

	inputs a, b;
	
	inputs aaa = (KEY.X | KEY.Z) & (KEY.N | KEY.M) & (KEY.S & KEY.T | KEY.U);
public:
	SCENE_CONSTRUCTOR(testscene)

	virtual void init() override {
		a = KEY.A;
		b = a;
		counter = 0;
	}

	virtual void draw() override {
		rect({ 32,32 }).at({ counter % 1280,counter / 980 }).colored(pallet::red).draw();
		console << counter;
		console << std::format("scene:{}", id());
	}

	virtual void update() override {
		counter++;
		if (systems.keyboard.Num2.down()) {
			change_scene(2, 60, false);
		}
		if (aaa.press()) {
			console << "test inputs";
		}
		if (a.press()) {
			console << "a";
		}
		if (b.press()) {
			console << "b";
		}
		if ((KEY.A & KEY.D | KEY.B & KEY.C).press()) {
			console << "aaa";
		}
	}
};
#undef KEY
class testscene2 : public scene<> {
private:
	uint counter = 0;
public:
	SCENE_CONSTRUCTOR(testscene2)

	virtual void init() override {
		counter = 0;
	}

	virtual void draw() override {
		rect({ 32,32 }).at({ counter % 1280,counter / 980 }).colored(pallet::green).draw();
		console << counter;
		console << std::format("scene:{}", id());
	}

	virtual void update() override {
		if (systems.keyboard.Num1.down()) {
			change_scene(1,40, true);
		}
		counter++;
	}
};

class evt : public::dx_engine::event {
private:
	uint _time;
public:
	evt(uint time) :_time(time) {}

	bool update(uint count) override {
		dx_engine::console >> "event" >> count;
		return count < _time;
	}
};

class evt2 : public::dx_engine::event {
private:
	uint _time;
public:
	evt2(uint time) :_time(time) {}

	bool update(uint count) override {
		dx_engine::console >> "event2" >> count;
		return count < _time;
	}
};

struct save_struct {
	int a, b, c, d;
	float e, f, g;
	std::string h;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(a, b, c, d, e, f, g, h);
	}
};

void GradBox(point<int> p1, point<int> p2, color c1, color c2, color c3, color c4)
{
	VERTEX2D Vertex[6];

	// 左上の頂点の情報をセット( 1ポリゴン目の第1頂点 )
	Vertex[0].pos.x = (float)p1.x;
	Vertex[0].pos.y = (float)p1.y;
	Vertex[0].pos.z = 0.0f;
	Vertex[0].rhw = 1.0f;
	Vertex[0].dif.r = c1.r;
	Vertex[0].dif.g = c1.g;
	Vertex[0].dif.b = c1.b;
	Vertex[0].dif.a = c1.a;
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;

	// 右上の頂点の情報をセット( 1ポリゴン目の第2頂点 )
	Vertex[1].pos.x = (float)p2.x;
	Vertex[1].pos.y = (float)p1.y;
	Vertex[1].pos.z = 0.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[1].dif.r = c2.r;
	Vertex[1].dif.g = c2.g;
	Vertex[1].dif.b = c2.b;
	Vertex[1].dif.a = c2.a;
	Vertex[1].u = 0.0f;
	Vertex[1].v = 0.0f;

	// 左下の頂点の情報をセット( 1ポリゴン目の第3頂点 )
	Vertex[2].pos.x = (float)p1.x;
	Vertex[2].pos.y = (float)p2.y;
	Vertex[2].pos.z = 0.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[2].dif.r = c3.r;
	Vertex[2].dif.g = c3.g;
	Vertex[2].dif.b = c3.b;
	Vertex[2].dif.a = c3.a;
	Vertex[2].u = 0.0f;
	Vertex[2].v = 0.0f;

	// 右下の頂点の情報をセット( 2ポリゴン目の第1頂点 )
	Vertex[3].pos.x = (float)p2.x;
	Vertex[3].pos.y = (float)p2.y;
	Vertex[3].pos.z = 0.0f;
	Vertex[3].rhw = 1.0f;
	Vertex[3].dif.r = c4.r;
	Vertex[3].dif.g = c4.g;
	Vertex[3].dif.b = c4.b;
	Vertex[3].dif.a = c4.a;
	Vertex[3].u = 0.0f;
	Vertex[3].v = 0.0f;

	// 2ポリゴン目の第2頂点は左下の頂点なのでコピー
	Vertex[4] = Vertex[2];

	// 2ポリゴン目の第3頂点は右上の頂点なのでコピー
	Vertex[5] = Vertex[1];

	// ポリゴンを2個描画
	if (DrawPolygon2D(Vertex, 2, DX_NONE_GRAPH, FALSE)) {
		console << "error";
	}
}
#endif

struct charactor {
	point<int> pos;

	void set_pos(point<int> p) {
		pos = p;
	}
	void update();
};

int main() {
	//scene_manager scenemanager;
	//scenemanager.add<testscene>(1);
	//scenemanager.add<testscene2>(2);
	//
	//color clr = pallet::white;
	//hsv hclr = pallet::white;
	//rect slider_rect{ point<uint>{32, 400} };
	//gui::slider<byte> slider_r(rect{ point<uint>{600, 32} }, { 16,128},pallet::red, 0, 255);
	//gui::slider<byte> slider_g(rect{ point<uint>{600, 32} }, { 16,192 }, pallet::green, 0, 255);
	//gui::slider<byte> slider_b(rect{ point<uint>{600, 32} }, { 16,256 }, pallet::blue, 0, 255);
	//gui::slider<byte> slider_a(rect{ point<uint>{600, 32} }, { 16,320 }, pallet::white, 0, 255);

	//gui::slider<int> slider_h(rect{ point<uint>{600, 32} }, { 640,128 }, pallet::red, 0, 360);
	//gui::slider<double> slider_s(rect{ point<uint>{600, 32} }, { 640,192 }, pallet::green, 0, 1.0);
	//gui::slider<double> slider_v(rect{ point<uint>{600, 32} }, { 640,256 }, pallet::blue, 0, 1.0);

	//gui::pulldown pldwn({ "A","BB","CCC","あいうえお" }, { 1000, 64 });
	//uint plid = 2;

	//auto f = [&]() {clock::stopwatch sw; sw.restart(); while (sw.get_sec() <= 10) {}; return; };

	//int id = thread_manager.add(f);
	animation anm("test2.bmp", { 4,3 });
	anm.add(0, { 0,1,2,3 }, 15, true);
	anm.add(1, { 8,9 }, 15, true);
	anm.set(0);
	double rate = 1.0;
	rect r({ 256,192 });
	r.at(window.size() / 2.0).colored(pallet::gray).blend(blend::none, 255).centered({ 92,92 });

	//script_manager script;
	//SCRIPT_ADD_CLASS_PROPERTY(script.get(), charactor, point<int>, pos);
	while (systems.update()) {
		window.title(std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage()));
		
		console >> std::format("{:5.2f}fps", systems.fps());
		console << systems.mouse.position();

		//if (thread_manager.get(id)) {
		//	console << "a";
		//}
		//
		//scenemanager.update();
		/*bool frgb = false, fhsv = false;

		if(slider_r(clr.r))frgb=true;
		if(slider_g(clr.g))frgb=true;
		if(slider_b(clr.b))frgb=true;
		if(slider_a(clr.a))frgb=true;

		if(slider_h(hclr.h))fhsv=true;
		if(slider_s(hclr.s))fhsv=true;
		if(slider_v(hclr.v))fhsv=true;

		if (frgb) hclr = clr;
		if (fhsv) clr = hclr;

		console << std::format("r:{},g:{},b:{}", clr.r, clr.g, clr.b);
		console << std::format("h:{},s:{},v:{}", hclr.h, hclr.s, hclr.v);
		console << plid;

		circle(64).at({640, 480}).blend(blend::alpha, clr.a).colored(clr).draw();
		//circle(64).at(systems.mouse.position()).blend(blend::alpha, clr.a).colored(hclr).draw();

		
		//circle(6).at({ 320, 640 }).blend(blend::alpha, 64).colored(pallet::black).fill(false).thick(5).draw();
		//circle(6).at({ 320, 640 }).blend(blend::none, 255).colored(pallet::white).fill(false).thick(3).draw();

		for (auto i : step(6)) {
			GradBox({ 320 + i * 30, 700 }, { 320 + (i + 1) * 30, 956 }, hsv(i * 60, 1, 1), hsv((i + 1) * 60, 1, 1), hsv(i * 60, 1, 1), hsv((i + 1) * 60, 1, 1));

		}
		GradBox({ 320, 700 }, { 500, 828 }, color(255,255,255), color(255, 255, 255), color(255, 255, 255, 0), color(255, 255, 255, 0));
		GradBox({ 320, 828 }, { 500, 956 }, color(255, 255, 255, 0), color(255, 255, 255, 0), color(0, 0, 0, 255), color(0, 0, 0, 255));

		pldwn(plid);*/
		if (systems.keyboard.Num0.down()) {
			anm.set(0, false);
		}
		if (systems.keyboard.Num1.down()) {
			anm.set(1,false);
		}
		r.at(systems.mouse.position());
		r.draw();
		anm.blend(blend::none, 255).at(window.size() / 2.0f).play();
		//r.extended(rate).rotateed(rate * 2).draw();
		//circle(8).colored(pallet::white).blend(blend::none, 255).at(window.size() / 2.0).draw();
		//circle(32).colored(pallet::black).centered({ -8,-8 }).rotateed(rate * 2).blend(blend::none, 255).at(window.size() / 2.0 - point<double>{256, 256}).draw();
		//circle(8).colored(pallet::white).blend(blend::none, 255).at(window.size() / 2.0 - point<double>{256, 256}).draw();
		//rate += 0.001;
		//rate = fmod(rate, 2.0);
	}

	return 0;
}
//https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=past&no=2506
#elif 0
#include"DxLib.h"

#define SCREEN_W		(640)			//ゲーム自体の画面の横幅
#define SCREEN_H		(480)			//ゲーム自体の画面の縦幅

// 表示タイプ
int hyouji_type;
// 整数倍表示の時のレターボックスの大きさ
int letterboxsize_x;
int letterboxsize_y;
// アスペクト比保持の時のレターボックスの大きさ
int letterboxsize_n_x;
int letterboxsize_n_y;
// ディスプレイ解像度
int disp_x;
int disp_y;
// 描画スクリーン
int main_screen;

//エンターキーを押したフレームカウント
int enter;

void letter_box() {
	// ディスプレイ解像度取得
	disp_x = GetSystemMetrics(SM_CXSCREEN);
	disp_y = GetSystemMetrics(SM_CYSCREEN);
	if (disp_x / (float)SCREEN_W >= disp_y / (float)SCREEN_H) {// 描画画面の比率より横に長いか同じ場合
		letterboxsize_y = (disp_y % SCREEN_H) / 2;
		letterboxsize_x = (disp_x - (disp_y / SCREEN_H) * SCREEN_W) / 2;
		letterboxsize_n_y = 0;
		letterboxsize_n_x = (disp_x - (disp_y * SCREEN_W / SCREEN_H)) / 2;
	}
	else {// 描画画面の比率より縦に長い場合
		letterboxsize_x = (disp_x % SCREEN_W) / 2;
		letterboxsize_y = (disp_y - (disp_x / SCREEN_W) * SCREEN_H) / 2;
		letterboxsize_n_x = 0;
		letterboxsize_n_y = (disp_y - (disp_x * SCREEN_H / SCREEN_W)) / 2;
	}
}
void screen_hyouji() {
	switch (hyouji_type) {
	case 0: {//オリジナル
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawRotaGraph(disp_x / 2, disp_y / 2, 1.0f, 0.0f, main_screen, FALSE, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	case 1: {//整数倍
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(letterboxsize_x, letterboxsize_y, disp_x - letterboxsize_x, disp_y - letterboxsize_y, main_screen, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	case 2: {//アスペクト比保持
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(letterboxsize_n_x, letterboxsize_n_y, disp_x - letterboxsize_n_x, disp_y - letterboxsize_n_y, main_screen, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	case 3: {//フル
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(0, 0, disp_x, disp_y, main_screen, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	}
}

int Enter_Check() {
	if (CheckHitKey(KEY_INPUT_RETURN))
		enter++;
	else
		enter = 0;
	return enter;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	hyouji_type = 0;

	//黒枠計算を関数化してみた
	letter_box();
	SetGraphMode(disp_x, disp_y, 16);

	if (DxLib_Init() == -1)return -1;

	main_screen = MakeScreen(SCREEN_W, SCREEN_H);// 描画用のスクリーン作成
	SetDrawScreen(main_screen);// 描画するスクリーンを変更

	//ループ。ここに鬼のようにコードを書き込む
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();

		if (Enter_Check() == 1) {// エンターキーを押した時のみ
			hyouji_type++;
			if (hyouji_type > 3)
				hyouji_type = 0;
		}


		//テスト用仮表示
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 211, 63), TRUE);
		DrawString(200, 100, "もしかして、見えちゃった？", GetColor(63, 0, 0));


		switch (hyouji_type) {
		case 0: {DrawString(0, 0, "オリジナル", GetColor(63, 0, 0)); break; }
		case 1: {DrawString(0, 0, "整数倍", GetColor(63, 0, 0)); break; }
		case 2: {DrawString(0, 0, "アスペクト比保持", GetColor(63, 0, 0)); break; }
		case 3: {DrawString(0, 0, "フル", GetColor(63, 0, 0)); break; }
		}

		//表示部分を関数化
		screen_hyouji();

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
#elif 0 //ボーダーレスウィンドウ
#include"DxLib.h"

#define SCREEN_W		(640)			//ゲーム自体の画面の横幅
#define SCREEN_H		(480)			//ゲーム自体の画面の縦幅

// 表示タイプ
int hyouji_type;
// 整数倍表示の時のレターボックスの大きさ
int letterboxsize_x;
int letterboxsize_y;
// アスペクト比保持の時のレターボックスの大きさ
int letterboxsize_n_x;
int letterboxsize_n_y;
// ディスプレイ解像度
int disp_x;
int disp_y;
// 描画スクリーン
int main_screen;

//エンターキーを押したフレームカウント
int enter;

void letter_box() {
	// ディスプレイ解像度取得
	disp_x = GetSystemMetrics(SM_CXSCREEN);
	disp_y = GetSystemMetrics(SM_CYSCREEN);
	if (disp_x / (float)SCREEN_W >= disp_y / (float)SCREEN_H) {// 描画画面の比率より横に長いか同じ場合
		letterboxsize_y = (disp_y % SCREEN_H) / 2;
		letterboxsize_x = (disp_x - (disp_y / SCREEN_H) * SCREEN_W) / 2;
		letterboxsize_n_y = 0;
		letterboxsize_n_x = (disp_x - (disp_y * SCREEN_W / SCREEN_H)) / 2;
	}
	else {// 描画画面の比率より縦に長い場合
		letterboxsize_x = (disp_x % SCREEN_W) / 2;
		letterboxsize_y = (disp_y - (disp_x / SCREEN_W) * SCREEN_H) / 2;
		letterboxsize_n_x = 0;
		letterboxsize_n_y = (disp_y - (disp_x * SCREEN_H / SCREEN_W)) / 2;
	}
}
void screen_hyouji() {
	switch (hyouji_type) {
	case 0: {//オリジナル DOT by DOT
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawRotaGraph(disp_x / 2, disp_y / 2, 1.0f, 0.0f, main_screen, FALSE, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	case 1: {//整数倍
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(letterboxsize_x, letterboxsize_y, disp_x - letterboxsize_x, disp_y - letterboxsize_y, main_screen, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	case 2: {//アスペクト比保持　最大表示
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(letterboxsize_n_x, letterboxsize_n_y, disp_x - letterboxsize_n_x, disp_y - letterboxsize_n_y, main_screen, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	case 3: {//フル 
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawExtendGraph(0, 0, disp_x, disp_y, main_screen, FALSE);
		SetDrawScreen(main_screen);
		break;
	}
	}
}

int Enter_Check() {
	if (CheckHitKey(KEY_INPUT_RETURN))
		enter++;
	else
		enter = 0;
	return enter;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	hyouji_type = 0;

	int i;
	int x, y, addX, addY;
	int DisplayNum;
	int RectX, RectY, SizeX, SizeY, IsPrimary;

	// モニタの数を取得する
	DisplayNum = GetDisplayNum();

	// モニタの数だけ繰り返し
	for (i = 0; i < DisplayNum; i++)
	{
		// モニタの情報を取得
		GetDisplayInfo(i, &RectX, &RectY, &SizeX, &SizeY, &IsPrimary);

		// プライマリモニタではなかったらループ終了
		if (IsPrimary == TRUE)
		{
			break;
		}
	}

	//黒枠計算を関数化してみた
	letter_box();
	

	// ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	// タスクバーなし設定
	SetWindowStyleMode(1);

	// ウィンドウの解像度をモニタの解像度と同じにする
	SetGraphMode(disp_x, disp_y, 32);

	// ウィンドウの位置をセット
	SetWindowPosition(RectX, RectY);

	if (DxLib_Init() == -1)return -1;

	main_screen = MakeScreen(SCREEN_W, SCREEN_H);// 描画用のスクリーン作成
	SetDrawScreen(main_screen);// 描画するスクリーンを変更

	//ループ。ここに鬼のようにコードを書き込む
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();

		if (Enter_Check() == 1) {// エンターキーを押した時のみ
			hyouji_type++;
			if (hyouji_type > 3)
				hyouji_type = 0;
		}


		//テスト用仮表示
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 211, 63), TRUE);
		DrawString(200, 100, "もしかして、見えちゃった？", GetColor(63, 0, 0));


		switch (hyouji_type) {
		case 0: {DrawString(0, 0, "オリジナル", GetColor(63, 0, 0)); break; }
		case 1: {DrawString(0, 0, "整数倍", GetColor(63, 0, 0)); break; }
		case 2: {DrawString(0, 0, "アスペクト比保持", GetColor(63, 0, 0)); break; }
		case 3: {DrawString(0, 0, "フル", GetColor(63, 0, 0)); break; }
		}

		//表示部分を関数化
		screen_hyouji();

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
//https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=view&no=4560
#elif 0
#include "DxLib.h"
constexpr int size_x = 1900;
constexpr int size_y = 1080;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int i;
	int x, y, addX, addY;
	int DisplayNum;
	int RectX, RectY, SizeX, SizeY, IsPrimary;

	// モニタの数を取得する
	DisplayNum = GetDisplayNum();

	// モニタの数だけ繰り返し
	for (i = 0; i < DisplayNum; i++)
	{
		// モニタの情報を取得
		GetDisplayInfo(i, &RectX, &RectY, &SizeX, &SizeY, &IsPrimary);

		// プライマリモニタではなかったらループ終了
		if (IsPrimary == TRUE)
		{
			break;
		}
	}

	// 使用するモニタを指定
	SetUseDisplayIndex(i);

	// ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	// タスクバーなし設定
	SetWindowStyleMode(1);

	// ウィンドウの解像度をモニタの解像度と同じにする
	SetGraphMode(SizeX, SizeY, 32);

	// ウィンドウの位置をセット
	SetWindowPosition(RectX, RectY);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	// メインループ
	x = 0;
	y = 0;
	addX = 16;
	addY = 16;
	while (ProcessMessage() == 0)
	{
		// 画面内を跳ね回る
		x += addX;
		y += addY;
		if (x < 0 || x > size_x - 64) addX = -addX;
		if (y < 0 || y > size_y - 64) addY = -addY;

		// 画面のクリア
		ClearDrawScreen();

		// 四角形の描画
		DrawBox(x, y, x + 64, y + 64, GetColor(255, 255, 255), TRUE);

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}
#elif 1
#include "dx_engine.h"

using namespace std::literals::chrono_literals;
using namespace dx_engine;


void init() {
	dx_engine::log.set(true, false);
	//window.fullscreen(true, fullscreen_type::borderless_dotbydot);
	window.size({ 1280,960 });
	window.background(pallet::lightskyblue);
	window.title("TEST");
	window.extends(systems.monitor_size().x / 1920.0);
	//file.load("resource.dat");

	systems.vsync(false);
	//systems.max_fps(N);
}
point<double> make_vector(double v, double a) {
	return point<double>{v* cos(a), v* sin(a)};
}

constexpr int wait(int f) {
	return (int)(1000 * f / 60.0);
}
#ifndef debug_string
#define debug_string(val) std::format("{}:{}",#val,val)
#endif
class enemy {
public:
	point<double> pos = {0,0};
	double speed = 0, angle = 90.0, anglespeed = 0;
	int32_t count = -10, step = 0;
	std::vector<std::string> script;

	enemy(const std::string& path) {
		auto f = file.get_line(path);
		std::erase_if(f, [](const std::string& s) {return s == ""; });
		script = f;
	}
	void update() {
		angle += anglespeed * systems.delta_sec_d() * 60.0;
		/*while (angle < 0) {
			angle += 360.0;
		}
		angle = fmod(angle, 360.0);*/
		pos += make_vector(speed*systems.delta_sec_d() * 60, radian(angle));
		draw();
		//if (!move_t.isReady()) {
		console << debug_string(angle);
		console << debug_string(anglespeed);
		console << debug_string(speed);
		console << debug_string(pos.to_string());
		//}
		count++;
		
	}
	void draw() {
		rect({ 64,64 }).at(pos).colored(pallet::blue).draw();
	}

	task wait(int f) {
		for (int i = 0; i < f; i++) {
			co_await ::wait(1);
		}
	}

	task move() {
#if 0
		while (true) {
			switch (count) {
			case 0: {//0
				speed = 3;
				anglespeed = radian_f(0);
				step++;
				co_await 1;
				break;
			}
			case 90: {//1
				speed = 2;
				anglespeed = radian_f(-1);
				step++;
				co_await 1;
				break;
			}
			case 180: {
				speed = 3;
				anglespeed = radian_f(0);
				step++;
				co_await 1;
				break;
			}
			case 270: {
				speed = 2;
				anglespeed = radian_f(-1);
				step++;
				co_await 1;
				break;
			}
			case 360: {
				speed = 3;
				anglespeed = radian_f(0);
				step++;
				co_return;
				break;
			}
			default: {
				co_await 1;
				break;
			}
			}
		}
#elif 1
		/*//while (true) {
			speed = 3;
			anglespeed = radian_f(0);
			step++;
			co_await ::wait(90);

			speed = 2;
			anglespeed = radian_f(-1);
			step++;
			co_await 1500ms;

			speed = 3;
			anglespeed = radian_f(0);
			step++;
			co_await 1500ms;

			speed = 2;
			anglespeed = radian_f(-1);
			step++;
			co_await 1500ms;

			speed = 3;
			anglespeed = radian_f(0);
			step++;
			co_return;
		//}*/

		for (auto& s : script) {
			s = replace_string(s, " ", "");
			auto code = split(s, ",");
			if (code.at(0) == "end") {
				co_return;
			}
			double v = atof(code.at(1).c_str());
			if (code.at(0) == "speed") {
				speed = v;
			}
			else if (code.at(0) == "angle") {
				angle = v;
			}
			else if (code.at(0) == "anglespeed") {
				anglespeed = v;
				/*while (anglespeed < 0) {
					anglespeed += 360.0;
				}
				anglespeed = fmod(anglespeed, 360.0);*/
			}
			else if (code.at(0) == "wait") {
				for (int i = 0; i < v; i++) {

				}
			}
			step++;
		}
#else
		speed = 3;
		anglespeed = radian_f(0);
		step++;
		co_await 1500;
		speed = 2;
		anglespeed = radian_f(-1);
		step++;
		co_await 1500;

		speed = 3;
		anglespeed = radian_f(0);
		step++;
		co_await 1500;

		speed = 2;
		anglespeed = radian_f(-1);
		step++;
		co_await 1500;

		speed = 3;
		anglespeed = radian_f(0);
		step++;
		co_await 1500;
#endif
	}
};

task Main() {
	std::vector<task> ary;
	enemy e1("test.txt"), e2("test2.txt");
	int c = 0;

	while (systems.update()) {
		console >> systems.fps();
		if (c == 0) {
			ary.push_back(e1.move());
		}
		if (c == 60) {
			ary.push_back(e2.move());
		}
		e1.update();
		if (c > 60) {
			e2.update();
		}
		c++;
		co_await 0;
	}
}

int main() {
	Main().wait();

	return 0;
}
#undef debug_string
#endif