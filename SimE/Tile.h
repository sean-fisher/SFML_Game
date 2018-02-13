#pragma once

#include <SFML/Graphics.hpp>

namespace SimE {
class Tile {
public:
	Tile();
	Tile(sf::Texture& texture);
	~Tile();

	void draw(int x, int y, sf::RenderWindow* rWindow);

private:
	sf::Sprite m_sprite;
};

}