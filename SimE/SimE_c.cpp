// SimE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimE_c.h"
#include "IOUtility.h"
#include <iostream>
#include "Control.h"
#include <algorithm>

namespace SimE {

Tile* SimE_c::testTile;
sf::RenderWindow* SimE_c::renderWindow;
size_t SimE_c::tileSize = 8;
sf::View* SimE_c::sView;
Tilemap* SimE_c::tileMap;
int SimE_c::debugMode;

void SimE_c::drawFrame() {
	renderWindow->clear();
	

	/////////////////////////////////////////////////////////
	// Draw the Map

	//Get the tile bounds we need to draw and Camera bounds
	sf::Vector2f bounds = sView->getSize();
	sf::Vector2f center = sView->getCenter();
	//MapLayer* currentLayer = entireMap[0];

	tileMap->drawAll(renderWindow, center, bounds);
}

void SimE_c::renderFrame() {

	renderWindow->display();
}
void SimE_c::processInput() {
	Control::updateAllInput();
}
void SimE_c::beat() {
	Alive::beatAll();
}
/*
void SimE_c::loadTestLevel(ImageCache* imageCache) {
	//Temporary level for testing
	currentMap = new MapLayer(40, 40);
	
	Tile* tile;
	int hash = IOUtility::getHashFromFilepath("Cop/idle_front.png");
	for (int y = 0; y < 40; ++y) {
		for (int x = 0; x < 40; x++) {
			if (y % 4 == 0) {
				tile = new Tile(imageCache->getTexture(hash));
			}
			else
				tile = new Tile(imageCache->getTexture(hash));
	
			currentMap->addTile(x, y, tile);
		}
	}
}*/
}