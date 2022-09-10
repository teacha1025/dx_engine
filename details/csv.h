#pragma once
#include <string>
#include <vector>
#include "def.h"
#include "point.h"


namespace dx_engine {
	class csv {
	private:
		std::string name = "";
		std::vector<std::vector<std::string>> data;
		point<uint> _size;
	public:
		/// <summary>
		/// csvを作成
		/// </summary>
		/// <param name="path">csvファイルのパス</param>
		/// <param name="split">区切り文字 デフォルトでは ','</param>
		csv(const std::string& path, char split = ',');

		/// <summary>
		/// csvのデータを取得
		/// </summary>
		/// <param name="position">取得するデータの座標</param>
		/// <returns>文字列のデータ</returns>
		std::string at(const point<uint>& position) const;

		/// <summary>
		/// csvの大きさを取得
		/// </summary>
		/// <returns>csvの行数×1行目の列数</returns>
		point<uint> size() const;
	};
}