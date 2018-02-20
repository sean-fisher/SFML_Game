#include "stdafx.h"
#include "AliveTile.h"

namespace SimE {
AliveTile::AliveTile() {
}


AliveTile::~AliveTile() {
}
void AliveTile::draw(sf::RenderWindow * rWindow) {

	m_sprite.setPosition(static_cast<float>(m_pos.x - m_width / 2), static_cast<float>(m_pos.y - m_height / 2));
	rWindow->draw(m_sprite);
}
}