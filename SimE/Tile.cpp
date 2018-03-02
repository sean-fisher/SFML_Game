#include "stdafx.h"
#include "Tile.h"
#include "defines.h"

#include <iostream>

namespace SimE {
Tile::Tile(sf::Texture & texture, float scaleX, float scaleY, bool flipDiagonally) {

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
				m_sprite.setOrigin(static_cast<float>(m_width)/*(m_height + m_width%m_height) + m_height*/, static_cast<float>(m_width)); // TEST: Bottom-left
				m_sprite.setScale(sf::Vector2f(scaleX, -scaleY));

			} else {
				// rotated ccw
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin(static_cast<float>(-m_width + m_height), static_cast<float>(m_width));
			}
		} else {
			if (scaleY < 0) {
				// rotated cw (CORRECT)
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin(static_cast<float>(m_width), 0.0f);

				m_sprite.setScale(sf::Vector2f(-scaleX, scaleY));
			} else {
				// rotated once and flipped x
				m_sprite.rotate(90);
				m_sprite.setScale(sf::Vector2f(-scaleX, scaleY));
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.rotate(180);
				m_sprite.setOrigin(static_cast<float>(-m_width + m_height), m_sprite.getOrigin().y);

			}

		}
	} else {
		m_sprite.setScale(sf::Vector2f(scaleX, scaleY));

		if (scaleX < 0) {
			if (scaleY > 0) {
				// only flipped x
				m_sprite.setOrigin(static_cast<float>(m_width), 0.0f);
			} else {
				// flipped x, y
				m_sprite.setOrigin(static_cast<float>(m_width), static_cast<float>(m_height));
			}

		} else {
			if (scaleY > 0) {
				// normal
				m_sprite.setOrigin(0.0f, 0.0f);
			} else {
				// flipped y
				m_sprite.setOrigin(0.0f, static_cast<float>(m_height));
			}

		}
	}
}

Tile::Tile(sf::Texture & texture, float scaleX, float scaleY, bool flipDiagonally, sf::IntRect cutoutBounds) {
	m_sprite.setTexture(texture, true);
	m_sprite.setTextureRect(cutoutBounds);
	sf::Vector2u size = texture.getSize();
	m_width = cutoutBounds.width;
	m_height = cutoutBounds.height;

	//m_sprite.setOrigin(m_width / 2, m_height / 2);
	if (flipDiagonally) {
		if (scaleX < 0) {
			if (scaleY < 0) {
				// rotated cw and flipped y
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin(static_cast<float>(m_width)/*(m_height + m_width%m_height) + m_height*/, static_cast<float>(m_width)); // TEST: Bottom-left
				m_sprite.setScale(sf::Vector2f(scaleX, -scaleY));

			} else {
				// rotated ccw
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin(static_cast<float>(-m_width + m_height), static_cast<float>(m_width));
			}
		} else {
			if (scaleY < 0) {
				// rotated cw (CORRECT)
				m_sprite.rotate(90);
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.setOrigin(static_cast<float>(m_width), 0);

				m_sprite.setScale(sf::Vector2f(-scaleX, scaleY));
			} else {
				// rotated once and flipped x
				m_sprite.rotate(90);
				m_sprite.setScale(sf::Vector2f(-scaleX, scaleY));
				int tempDim = m_width;
				m_width = m_height;
				m_height = tempDim;
				m_sprite.rotate(180);
				m_sprite.setOrigin(static_cast<float>(-m_width + m_height), m_sprite.getOrigin().y);

			}

		}
		m_sprite.setOrigin(m_sprite.getOrigin().y - texture.getSize().y - m_height, m_sprite.getOrigin().x + texture.getSize().x + m_width * 3);
	} else {
		m_sprite.setScale(sf::Vector2f(scaleX, scaleY));

		if (scaleX < 0) {
			if (scaleY > 0) {
				// only flipped x
				m_sprite.setOrigin(static_cast<float>(m_width), 0.0f);
			} else {
				// flipped x, y
				m_sprite.setOrigin(static_cast<float>(m_width), static_cast<float>(m_height));
			}

		} else {
			if (scaleY > 0) {
				// normal
				m_sprite.setOrigin(0.0f, 0.0f);
			} else {
				// flipped y
				m_sprite.setOrigin(0.0f, static_cast<float>(m_height));
			}

		}
	}
	m_sprite.setOrigin(m_sprite.getOrigin().x, m_sprite.getOrigin().y - texture.getSize().y + m_height);
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