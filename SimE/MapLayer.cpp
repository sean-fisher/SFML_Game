#include "stdafx.h"
#include "MapLayer.h"

#include <algorithm>
#include <fstream>

namespace SimE {

SimE::MapLayer::MapLayer(size_t w, size_t h) {
	SetDimensions(w, h);
	m_width = w;
	m_height = h;
	m_tileSize = 8;
}

MapLayer::~MapLayer() {
}

void SimE::MapLayer::addTile(size_t x, size_t y, Tile * tile) {
	m_mapLayer[x][y] = tile;
}

void MapLayer::addTile(AliveTile * aTile) {
	m_aliveTiles.push_back(aTile);
}

void MapLayer::addTile(size_t x, size_t y, sf::Texture * texture, float scaleX, float scaleY, int rotationDegrees) {
	if (m_mapLayer[x][y]) {
		m_mapLayer[x][y]->setTexture(texture);
	} else {
		m_mapLayer[x][y] = new Tile(*texture, scaleX, scaleY, rotationDegrees);
		m_mapLayer[x][y]->setTexture(texture);
	}
}
void MapLayer::addTile(size_t x, size_t y, sf::Texture * texture, float scaleX, float scaleY, int rotationDegrees, sf::IntRect bounds) {
	if (m_mapLayer[x][y]) {
		m_mapLayer[x][y]->setTexture(texture);
	} else {
		m_mapLayer[x][y] = new Tile(*texture, scaleX, scaleY, rotationDegrees, bounds);
		m_mapLayer[x][y]->setTexture(texture);
	}
}

Tile * MapLayer::getTile(size_t x, size_t y) {
	size_t width = m_mapLayer.size();
	if (x < width) {
		size_t height = m_mapLayer[x].size();
		if (y < height) {
			return m_mapLayer[x][y];
		}
	}
	return nullptr;
}

void MapLayer::draw(sf::RenderWindow * renderWindow, sf::Vector2f center, sf::Vector2f bounds) {

	Tile* tile;

	//Loop through and draw each tile
	//We're keeping track of two variables in each loop. How many tiles
	//we've drawn (x and y), and which tile on the map we're drawing (tileX
	//and tileY)
	int tilesDrawn = 0;

	// bounds.x is only from the center to the edge

	int firstX = static_cast<int>((center.x - bounds.x / 2) / m_tileSize);// % mapWidth;
	int firstY = static_cast<int>((center.y - bounds.y / 2) / m_tileSize);// % mapHeight; // 



	int totalY = std::min(static_cast<int>(bounds.y / m_tileSize), m_height);
	int totalX = std::min(static_cast<int>(bounds.x / m_tileSize), m_width);

	int tileX = firstX < 0 ? 0 : firstX-16;
	int tileY = firstY < 0 ? 0 : firstY-16;

	for (int y = tileY; y < totalY + tileY + 32; y++) {

		for (int x = tileX; x < totalX + tileX + 32; x++) {

			//Get the tile we're drawing
			tile = getTile(x, y);
			if (tile != nullptr) {
				tile->draw((x * m_tileSize), (y * m_tileSize), renderWindow);
				tilesDrawn++;
			}
		}
	}

	///////////////////////////////////////////////
	// draw sprites for this layer
	for (size_t i = 0; i < m_aliveTiles.size(); i++) {
		m_aliveTiles[i]->draw(renderWindow);
	}
}

void SimE::MapLayer::SetDimensions(size_t w, size_t h) {
	m_mapLayer.resize(w);

	for (size_t i = 0; i < w; i++) {
		m_mapLayer.at(i).resize(h, 0);
	}
}

}