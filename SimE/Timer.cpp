#pragma once
#include "stdafx.h"
#include "Timer.h"
#include <iostream>

namespace SimE {

float Timer::s_fDelta;
float Timer::s_fFPS;
float Timer::s_fElapsed;
sf::Clock Timer::s_clock;

void Timer::init(sf::Clock& clock) {
	s_clock = clock;
}
void Timer::tick() {
	float elapsed = s_clock.getElapsedTime().asSeconds();
	s_fDelta = elapsed - s_fElapsed;
	s_fElapsed = elapsed;
}
float Timer::getExactFPS() {
	return 1 / s_fDelta;
}
int Timer::getFPS() {
	return 0;
}
}