#include "stdafx.h"
#include "Obstacle.h"

namespace SimE {
Obstacle::Obstacle() {
}


Obstacle::~Obstacle() {
}

void Obstacle::setCollider(int width, int height) {
	if (m_collider == nullptr) {
		m_collider = new SquareCollider(width, height, m_pos, true);
		CollisionLayers::addCollider(m_collider);
	}
}
void Obstacle::setSprite(sf::Texture * tex) {
	m_aTile = new AliveTile();
	m_aTile->setTexture(tex);
}
}