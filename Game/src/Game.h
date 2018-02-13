#pragma once

#include <string>
#include <sfml/Graphics.hpp>


class Game {
public:
	Game() {};
	~Game() {};
	int start(int screenWidth, int screenHeight, std::string windowTitle);
	static void loadTextures();
private:

	static sf::RenderWindow* m_sRenderWindow;

	static int m_sScreenHeight;
	static int m_sScreenWidth;
	static std::string m_sWindowTitle;
};