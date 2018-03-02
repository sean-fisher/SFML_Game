#pragma once

#include <SFML/Graphics.hpp>

namespace SimE {
class Tile {
public:
	Tile() {};
	Tile(sf::Texture& texture, float scaleX, float scaleY, bool flipDiagonally);
	Tile(sf::Texture& texture, float scaleX, float scaleY, bool flipDiagonally, sf::IntRect cutoutBounds);
	~Tile();
	void setTexture(sf::Texture* texture);

	void draw(int x, int y, sf::RenderWindow* rWindow);

protected:
	sf::Sprite m_sprite;
	int m_width;
	int m_height;
};

}