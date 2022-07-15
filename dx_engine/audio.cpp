#include <string>
#include <DxLib.h>
#include "audio.h"
#include "range.h"
#include "details.h"


namespace dx_engine {
	extern detail::_console console;
	audio::audio(const std::string& path, bool loop) {
		_handle = LoadSoundMem(path.c_str(), 8);
		_loop = loop;
		ChangeVolumeSoundMem((int)(_volume * (235 + (abs(_pan)) * 20)), _handle);
		ChangePanSoundMem((int)(_pan * 255), _handle);
	}

	audio& audio::pan(range<-1.0f, 1.0f> panpal) {
		if (_pan != panpal.get()) {
			_pan = panpal;
			ChangeVolumeSoundMem((int)(_volume * (235 + (abs(_pan)) * 20)), _handle);
			ChangePanSoundMem((int)(_pan * 255), _handle);
		}

		return *this;
	}
	audio& audio::volume(range<0.0f, 1.0f> value) {
		if (_volume != value.get()) {
			_volume = value;
			ChangeVolumeSoundMem((int)(_volume * (235 + (abs(_pan)) * 20)), _handle);
			ChangePanSoundMem((int)(_pan * 255), _handle);
		}

		return *this;
	}

	void audio::play() {
		if (_handle > 0) {
			PlaySoundMem(_handle, _loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK, _start_at_head ? 1 : 0);
		}
	}
	void audio::pause() {
		if (_handle > 0) {
			if (is_playing()) {
				StopSoundMem(_handle);
			}
			_start_at_head = false;
		}
	}
	void audio::stop() {
		if (_handle > 0) {
			if (is_playing()) {
				StopSoundMem(_handle);
			}
			_start_at_head = true;
		}
	}

	bool audio::is_playing() const {
		if (_handle > 0) {
			return CheckSoundMem(_handle) != 0 ? true : false;
		}
		else {
			return false;
		}
	}
}