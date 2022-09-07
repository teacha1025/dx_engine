#pragma once
#include <string>
#include "def.h"
#include "range.h"


namespace dx_engine {
	class audio {
	private:
		int _handle = 0;
		float _pan = 0.0f, _volume = 1.0f;
		bool _loop;
		bool _playing = false, _start_at_head = true;
	public:
		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		audio() = default;
		/// <summary>
		/// パスから音声を作成
		/// </summary>
		/// <param name="path">音声のパス</param>
		/// <param name="loop">音声をループさせるか</param>
		audio(const std::string& path, bool loop);

		/// <summary>
		/// パンの設定
		/// </summary>
		/// <param name="panpal">音源の位置[-1.0f, 1.0f] +側は右、－側は左</param>
		audio& pan(range<-1.0f, 1.0f> panpal);
		/// <summary>
		/// 音量の設定
		/// </summary>
		/// <param name="value">音量[0.0f-1.0f]</param>
		audio& volume(range<0.0f, 1.0f> value);

		/// <summary>
		/// 音声の再生を開始
		/// </summary>
		void play();
		/// <summary>
		/// 音声を一時停止する
		/// </summary>
		void pause();
		/// <summary>
		/// 音声を停止する
		/// </summary>
		void stop();

		/// <summary>
		/// 音声が再生中かどうか確認する
		/// </summary>
		/// <returns>trueなら音声が再生されている</returns>
		bool is_playing() const;
	};
}