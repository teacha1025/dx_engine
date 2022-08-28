#if 1
#include "dx_engine.h"

namespace dx_engine {

}

using namespace dx_engine;

define N = 60.0;

void init() {
	dx_engine::log.set(true, false);
	window.fullscreen(false, fullscreen_type::borderless_dotbydot);
	window.size({ 1280,960 });
	window.background(pallet::lightskyblue);
	window.title("TEST");
	window.extends(1);
	//file.load("resource.dat");

	//systems.vsync(false);
	//systems.max_fps(N);
}
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

int main() {
	scene_manager scenemanager;
	scenemanager.add<testscene>(1);
	scenemanager.add<testscene2>(2);
	while (systems.update()) {
		window.title(std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage()));
		
		console << std::format("{:5.2f}fps", systems.fps());
		scenemanager.update();
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
#elif 1 //ボーダーレスウィンドウ
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
#else
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
#endif