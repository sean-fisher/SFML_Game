#include "stdafx.h"

#include <sfml/Graphics.hpp>
#include <SimE/SimE_c.h>
#include "Game.h"
#include <SimE/IOUtility.h>
#include <SimE/Tile.h>

int main() {

	Game game = Game();
	game.start(640, 480, "Game Title");



	return 0;
}

// Game
sf::RenderWindow* Game::m_sRenderWindow;
int Game::m_sScreenHeight;
int Game::m_sScreenWidth;
std::string Game::m_sWindowTitle;

int Game::start(int screenWidth, int screenHeight, std::string windowTitle) {
	m_sScreenWidth = screenWidth;
	m_sScreenHeight = screenHeight;
	m_sWindowTitle = windowTitle;

	sf::RenderWindow renderWindow(sf::VideoMode(m_sScreenWidth, m_sScreenHeight), m_sWindowTitle);
	m_sRenderWindow = &renderWindow;
	SimE::SimE_c::setRenderWindow(&renderWindow);

	loadTextures();
	sf::Texture spriteTexture;
	SimE::IOUtility::getTexture(SimE::CHARACTER, "Cop/idle_front.png", &spriteTexture);
	SimE::Tile testTile(spriteTexture);

	renderWindow.setVerticalSyncEnabled(false);

	// main game loop
	while (renderWindow.isOpen()) {

		sf::Event event;
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}

		//sf::CircleShape shape(100.f);
		//shape.setFillColor(sf::Color::Green);

		SimE::SimE_c::processInput();
		SimE::SimE_c::beat();
		SimE::SimE_c::drawFrame();
		// draw more here if absolutely necessary or for testing purposes
		SimE::SimE_c::renderFrame();
	}

	return 0;
}

void Game::loadTextures() {

	sf::Texture spriteTexture;
	SimE::IOUtility::getTexture(SimE::CHARACTER, "Cop/idle_front.png", &spriteTexture);
	
}
