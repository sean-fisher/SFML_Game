#pragma once

#include <string.h>
#include <sfml/Graphics.hpp>
#include "ImageCache.h"
#include "Tile.h"
#include "Camera2D.h"
#include "Tilemap.h"

namespace SimE {
class SimE_c {
public:
	static void drawFrame();
	static void renderFrame();
	static void processInput();
	static void beat();

	static void setTileSize(size_t size) { tileSize = size; }
	static void setView(sf::View* view) { sView = view; }
	static void setMap(Tilemap* map) { tileMap = map; }
	//static void addMapLayer(MapLayer& map) { entireMap.push_back(&map); }

	static void setRenderWindow(sf::RenderWindow* rWindow) { renderWindow = rWindow; }
	static int isDebug() { return debugMode; }
	static void setDebug(int mode) { debugMode = mode; }

private:
	static sf::RenderWindow* renderWindow;

	static Tile* testTile;

	static sf::View* sView;

	static SimE::Tilemap* tileMap;

	static size_t tileSize;

	static int debugMode;
};
}