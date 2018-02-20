#include "stdafx.h"
#include "Tile.h"
#include <iostream>

namespace SimE {
Tile::Tile(sf::Texture & texture, float scaleX, float scaleY, bool flipDiagonally) {

	static int test = 0;

	m_sprite.setTexture(texture, true);
	sf::Vector2u size = texture.getSize();
	m_width = size.x;
	m_height = size.y;

	//m_sprite.setOrigin(m_width / 2, m_height / 2);
	if (flipDiagonally) {
		if (scaleX < 0) {
			if (scaleY < 0) {
				// rotated cw and flipped y
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin((m_height + m_width%m_height) + m_height, m_width);
				m_sprite.setScale(sf::Vector2f(scaleX, -scaleY));

			} else {
				// rotated ccw
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin(-(m_height + m_width%m_height), m_width);
			}
		} else {
			if (scaleY < 0) {
				// rotated cw (CORRECT)
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin(m_width, 0);

				m_sprite.setScale(sf::Vector2f(-scaleX, scaleY));
			} else {
				// rotated once and flipped x
				m_sprite.rotate(90);
				m_sprite.setScale(sf::Vector2f(-scaleX, scaleY));
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.rotate(180);
				m_sprite.setOrigin(-(m_height + m_width%m_height), m_sprite.getOrigin().y);

			}

		}
	} else {
		m_sprite.setScale(sf::Vector2f(scaleX, scaleY));

		if (scaleX < 0) {
			if (scaleY > 0) {
				// only flipped x
				m_sprite.setOrigin(m_width, 0);
			} else {
				// flipped x, y
				m_sprite.setOrigin(m_width, m_height);
			}

		} else {
			if (scaleY > 0) {
				// normal
				m_sprite.setOrigin(0, 0);
			} else {
				// flipped y
				m_sprite.setOrigin(0, m_height);
			}

		}
	}
}

Tile::~Tile() {
}

void Tile::setTexture(sf::Texture* texture) {
	
	m_sprite.setTexture(*texture);
	sf::Vector2u size = texture->getSize();
	m_width = size.x;
	m_height = size.y;
}

void Tile::draw(int x, int y, sf::RenderWindow * rWindow) {
	sf::Vector2f temp = m_sprite.getOrigin();
	m_sprite.setPosition(static_cast<float>(x), static_cast<float>(y - m_height));
	rWindow->draw(m_sprite);
}
}