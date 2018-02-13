#include "stdafx.h"
#include "Tile.h"

namespace SimE {
Tile::Tile(sf::Texture & texture) {
	m_sprite.setTexture(texture, true);
}

Tile::~Tile() {
}

void Tile::draw(int x, int y, sf::RenderWindow * rWindow) {

	m_sprite.setPosition((int) x, (int) y);
	rWindow->draw(m_sprite);
}
}