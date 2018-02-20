#include "stdafx.h"
#include "Alive.h"

namespace SimE {

std::vector<Alive*> Alive::m_sAllAlive;

Alive::Alive() {
}


Alive::~Alive() {
}
void Alive::beatAll() {
	std::for_each(m_sAllAlive.begin(), m_sAllAlive.end(), [](Alive* a) {
		a->beat();
	});
}
bool Alive::birth() {

	m_sAllAlive.push_back(this);
	return true;
}
void Alive::setSprite(sf::Texture * tex) {
	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*tex);
}
}