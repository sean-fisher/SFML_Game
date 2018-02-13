// SimE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimE_c.h"
#include "IOUtility.h"

namespace SimE {

Tile* SimE_c::testTile;
sf::RenderWindow* SimE_c::renderWindow;

void SimE_c::drawFrame() {
	renderWindow->clear();

	// draw everything
	if (testTile != nullptr) {
		testTile->draw(0, 0, renderWindow);
	} else {
		sf::Texture* spriteTexture = new sf::Texture();
		IOUtility::getTexture(SimE::CHARACTER, "Cop/idle_front.png", spriteTexture);
		testTile = new Tile(*spriteTexture);
	}
}

void SimE_c::renderFrame() {

	renderWindow->display();
}
void SimE_c::processInput() {

}
void SimE_c::beat() {
}
}