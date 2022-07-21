#pragma once
namespace dx_engine {
	enum class blend {
		none = 0, //ノーブレンド
		alpha = 1, //αブレンド
		add = 2, //加算ブレンド
		sub = 3, //減算ブレンド
		mul = 4, //乗算ブレンド
		dest = 8, //カラーは更新されない
		inv_dest = 9, //描画先の色の反転値を掛ける
		inv_src = 10, //描画元の色を反転する
		mul_alpha = 11,	//アルファチャンネル考慮付き乗算ブレンド
		pma_alpha = 17, //乗算済みαブレンドモードのαブレンド
		pma_add = 18, //乗算済みαブレンドモードの加算ブレンド
		pma_sub = 19, //乗算済みαブレンドモードの減算ブレンド
		pma_inv_src = 20, //乗算済みαブレンドモードの描画元の色を反転する
	};

	enum class font_type {
		normal = 0, //ノーマルフォント
		edge = 1, //エッジ付きフォント
		anti_aliasing = 2, //アンチエイリアシングフォント
		edged_anti_aliasing = 3, //エッジ付きアンチエイリアシングフォント
	};
}