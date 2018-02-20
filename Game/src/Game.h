#pragma once

#include <string>
#include <sfml/Graphics.hpp>
#include "SimE/ImageCache.h"


class Game {
public:
	Game() {};
	~Game() {};
	int start(int screenWidth, int screenHeight, std::string windowTitle, int maxFPS, bool vsyncEnabled, int windowStyle);
	static void loadTextures(SimE::ImageCache& cache);
private:

	static SimE::ImageCache* imageCache;
	static sf::RenderWindow* m_sRenderWindow;

	static int m_sScreenHeight;
	static int m_sScreenWidth;
	static std::string m_sWindowTitle;
};