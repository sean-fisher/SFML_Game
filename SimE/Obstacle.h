#pragma once
#include "Alive.h"
#include "Collision.h"
#include "AliveTile.h"

namespace SimE {
class Obstacle :
	public Alive {
public:
	Obstacle();
	~Obstacle();

	void setCollider(int width, int height);
	void setSprite(sf::Texture* tex) override;
	AliveTile* getTile() {
		return m_aTile;
	};
protected:

	Collider* m_collider;
	AliveTile* m_aTile;
};

}