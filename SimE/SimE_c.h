#pragma once

#include <string.h>
#include <sfml/Graphics.hpp>
#include "ImageCache.h"
#include "Tile.h"

namespace SimE {
class SimE_c {
public:
	static void drawFrame();
	static void renderFrame();
	static void processInput();
	static void beat();

	static void setRenderWindow(sf::RenderWindow* rWindow) { renderWindow = rWindow; }

private:
	ImageCache m_imageCache;
	static sf::RenderWindow* renderWindow;

	static Tile* testTile;
};
}