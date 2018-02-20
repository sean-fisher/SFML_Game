#pragma once

#include <sfml/Graphics.hpp>
#include <sfml/Window.hpp>

#include "Tile.h"

namespace SimE {

/*
When you need something that is drawn outside of the tile map, such as an enemy, player, or treasure chest,
you will want to use an Alive so that it can be interacted with, and an AliveTile so its image can move on top of a MapLayer
*/
class AliveTile :
	public Tile {
public:
	AliveTile();
	~AliveTile();

	void draw(sf::RenderWindow* rWindow);
	void setPosition(sf::Vector2i pos) { m_pos = pos; }

private:
	sf::Vector2i m_pos;
};
}