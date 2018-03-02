#pragma once
#include <vector>
#include <sfml/Graphics.hpp>
#include <iostream>

#include "Tile.h"
#include "AliveTile.h"

namespace SimE {


class MapLayer {
public:
	MapLayer(size_t w, size_t h);
	~MapLayer();

	void addTile(size_t x, size_t y, Tile* tile);
	void addTile(AliveTile* aTile);
	void addTile(size_t x, size_t y, sf::Texture* texture, float scaleX, float scaleY, int rotationDegrees);
	void addTile(size_t x, size_t y, sf::Texture* texture, float scaleX, float scaleY, int rotationDegrees, sf::IntRect bounds);
	Tile* getTile(size_t x, size_t y);

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	void draw(sf::RenderWindow* renderWindow, sf::Vector2f center, sf::Vector2f bounds);

	int layerNum;

private:
	std::vector<std::vector<Tile*>> m_mapLayer;
	std::vector<AliveTile*> m_aliveTiles;

	int m_width;
	int m_height;
	int m_tileSize;

	void SetDimensions(size_t w, size_t h);
};

}