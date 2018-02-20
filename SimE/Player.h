#pragma once

#include "Alive.h"
#include "AliveTile.h"
#include "Collision.h"
#include <sfml/Window.hpp>

namespace SimE {
class Player : public Alive {
public:
	Player();
	~Player();
	void processInput();

	bool beat() override;

	void setView(sf::View* view) { m_view = view; }
	void setCollider(int width, int height);
	void setSprite(sf::Texture* tex);
	AliveTile* getTile() {
		return m_aTile;
	};

private:

	sf::Vector2f m_fPos;
	float m_speed;

	sf::View* m_view;

	Collider* m_collider;
	AliveTile* m_aTile;
};

}