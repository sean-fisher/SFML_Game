#pragma once

#include <vector>
#include <map>

#include "MapLayer.h"
#include "ImageCache.h"
#include "AliveTile.h"

namespace SimE {
class Tilemap {
public:
	Tilemap(int width, int height, std::string mapName, ImageCache* imageCache, bool isXML, std::vector<int> layersToSkip);
	void loadAllLayers(int width, int height, std::string mapName, std::vector<int> layersToSkip);
	void addAliveTileToLayer(AliveTile* aTile, int layer);
	void drawAll(sf::RenderWindow* renderWindow, sf::Vector2f center, sf::Vector2f bounds);

private:
	ImageCache* m_imageCache;
	std::map<int, MapLayer*> m_layers;
	bool loadTilemapLayerFromCSV(const std::string mapFileName, ImageCache* imageCache, MapLayer* in);
	bool loadTilemapFromTMX(const std::string mapFileName, ImageCache* imageCache, std::vector<int> layersToSkip);
};
}