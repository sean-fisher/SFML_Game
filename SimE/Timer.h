#pragma once
#include <sfml/Window.hpp>

namespace SimE {
class Timer {
public:
	static void init(sf::Clock& clock);
	static void tick();
	static float delta() {
		return s_fDelta;
	};
	static float getExactFPS();
	static int getFPS();
private:
	static float s_fDelta;
	static float s_fFPS;
	static float s_fElapsed;
	static sf::Clock s_clock;
};
}