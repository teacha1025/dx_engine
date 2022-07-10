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
		audio(const std::string& path, bool loop);

		audio& pan(range<-1.0f, 1.0f> panpal);
		audio& volume(range<0.0f, 1.0f> value);

		void play();
		void pause();
		void stop();

		bool is_playing() const;
	};
}