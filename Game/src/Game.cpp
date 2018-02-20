#include "stdafx.h"

#include <sfml/Graphics.hpp>
#include <SimE/SimE_c.h>
#include "Game.h"
#include <SimE/IOUtility.h>
#include <SimE/Tile.h>
#include <SimE/Camera2D.h>
#include <SimE/enums.h>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <SimE/Player.h>
#include <SimE/Control.h>
#include <SimE/Obstacle.h>
#include <SimE/Timer.h>
#include <SimE/Tilemap.h>

#define DEBUG_MODE

enum TestModes {
	DEBUG_NO_LIMITS = 0,
	DEBUG_DRAW_DOUBLE = 1,
	RELEASE_60 = 2,
	RELEASE_30 = 3
};

int main() {

	int screenMode   = sf::Style::Default;
	int screenWidth  = 1920 / 2;
	int screenHeight = 1080 / 2;

	SimE::SimE_c::setDebug(DEBUG_NO_LIMITS);
	Game game = Game();

	switch (SimE::SimE_c::isDebug()) {
	case DEBUG_NO_LIMITS:
		game.start(screenWidth, screenHeight, "Debug Mode", 1000, false, screenMode);
		break;
	case DEBUG_DRAW_DOUBLE:
		game.start(screenWidth, screenHeight, "Debug Mode", 1000, false, screenMode);
		break;
	case RELEASE_60:
		game.start(screenWidth, screenHeight, "Release Mode", 60, true, screenMode);
		break;
	case RELEASE_30:
		game.start(screenWidth, screenHeight, "Release Mode", 30, true, screenMode);
		break;
	}

	return 0;
}

// Game
sf::RenderWindow* Game::m_sRenderWindow;
int Game::m_sScreenHeight;
int Game::m_sScreenWidth;
std::string Game::m_sWindowTitle;
SimE::ImageCache* Game::imageCache;

int Game::start(int screenWidth, int screenHeight, std::string windowTitle, int maxFPS, bool vsyncEnabled, int windowStyle) {

	////////////////////////////////////////////////////
	// SET UP THE WINDOW

	// set the window settings
	m_sScreenWidth = screenWidth;
	m_sScreenHeight = screenHeight;
	m_sWindowTitle = windowTitle;

	// set openGL settings
	sf::ContextSettings settings;
	settings.depthBits = 2;
	settings.stencilBits = 1;
	settings.antialiasingLevel = 40;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	// create an SFML RenderWindow
	sf::RenderWindow renderWindow(sf::VideoMode(m_sScreenWidth, m_sScreenHeight), m_sWindowTitle, windowStyle);// , settings);
	m_sRenderWindow = &renderWindow;
	SimE::SimE_c::setRenderWindow(&renderWindow);
	renderWindow.setFramerateLimit(maxFPS);
	renderWindow.setVerticalSyncEnabled(vsyncEnabled);

	// create a view
	sf::View view(sf::Vector2f(200, 100), sf::Vector2f(screenWidth, screenHeight));
	renderWindow.setView(view);
	SimE::SimE_c::setView(&view);
	// zoom to appropriate level
	view.zoom(.5f);

	// keep track of FPS
	sf::Clock clock;
	/*float lastTime = 0;
	float sec = 0;*/
	SimE::Timer::init(clock);

	////////////////////////////////////////////////////
	// SET UP THE TILESET AND TILEMAP

	// get the imageCache singleton for loading sprite textures
	imageCache = SimE::ImageCache::singleton();

	// load the Tileset; right now this contains every map tile.
	imageCache->loadTileset("ss_All");

	// load the tilemap
	std::vector<int> layersToSkip = { 3, 5};
	SimE::Tilemap tilemap(16, 16, "Rotate_test", imageCache, true, layersToSkip);
	SimE::SimE_c::setMap(&tilemap);
	int maxlayer = 0;

	//////////////////////////////////////////////////
	// CREATE OBJECTS FOR TESTING

	// create a player
	sf::Texture spriteTexture;
	int copHash = SimE::IOUtility::getHashFromFilepath("Cop/idle_front.png");
	imageCache->loadTexture(SimE::CHARACTER, "Cop/idle_front.png", &spriteTexture, copHash);
	SimE::Player player;
	player.setPos(40, 0);
	player.birth();
	player.setView(&view);
	player.setSprite(imageCache->getTexture(copHash));
	player.setCollider(16, 32);
	tilemap.addAliveTileToLayer(player.getTile(), 2);

	// create a test collider
	sf::Texture testTexture;
	int testHash = SimE::IOUtility::getHashFromFilepath("fun.png");
	imageCache->loadTexture(SimE::TEST, "fun.png", &testTexture, testHash);
	SimE::Obstacle col;
	//col.birth();
	//col.setSprite(imageCache->getTexture(testHash));
	//col.setCollider(64, 64);
	//tilemap.addAliveTileToLayer(col.getTile(), 0);

	//////////////////////////////////////////////////
	// START RECEIVING INPUT
	SimE::Control::init();

	//////////////////////////////////////////////////
	// ENTER THE MAIN GAME LOOP
	while (renderWindow.isOpen()) {

		SimE::Timer::tick();
		
		static float sec = 0;
		float currentTime = SimE::Timer::delta();
		sec += (currentTime);
		if (sec > .5f) {
			std::cout << SimE::Timer::getExactFPS() << std::endl;
			sec = 0;
		}
		sf::Event event;
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SimE::SimE_c::processInput();
		SimE::SimE_c::beat();
		SimE::SimE_c::drawFrame();
		// draw more here if absolutely necessary or for testing purposes
		SimE::SimE_c::renderFrame();
		/*static int v = 1;
		v++;
		static int s = -1;
		if (v > 300) {
			v = 0; 
			s *= -1;
		}
		//view.move(s, 0);
		if (s > 0) {
			view.zoom(1 + 1 * currentTime);

		} else {

			view.zoom(1 - 1 * currentTime);
		}*/

		renderWindow.setView(view);
	}

	return 0;
}

void Game::loadTextures(SimE::ImageCache& cache) {

	sf::Texture spriteTexture;
	SimE::IOUtility::getTexture(SimE::CHARACTER, "Cop/idle_front.png", &spriteTexture);
	
}
