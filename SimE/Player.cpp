#include "stdafx.h"
#include "Player.h"
#include "Control.h"
#include "Timer.h"

namespace SimE {
Player::Player() {
	m_speed = 2.0f;//100.0f;
}


Player::~Player() {
}
void Player::processInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

	}
}
bool Player::beat() {

	m_collider->setLastPos(m_pos);

	if (Control::isDown(Input::LEFT)) {
		m_fPos.x -= m_speed;// *Timer::delta();
	}
	if (Control::isDown(Input::RIGHT)) {
		m_fPos.x += m_speed;// * Timer::delta();
	}

	if (Control::isDown(Input::UP)) {
		m_fPos.y -= m_speed;// * Timer::delta();
	}
	if (Control::isDown(Input::DOWN)) {
		m_fPos.y += m_speed;// * Timer::delta();
	}
	if (Control::isDown(Input::L)) {
		m_view->zoom(.9f);
	}
	if (Control::isDown(Input::R)) {
		m_view->zoom(1.1f);
	}
	static bool subPressedLast = false;
	static bool subPressedNow = false;
	subPressedNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
	if (subPressedNow && !subPressedLast) {
		m_view->zoom(2);
	}
	subPressedLast = subPressedNow;

	static bool addPressedLast = false;
	static bool addPressedNow = false;
	addPressedNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Add);
	if (addPressedNow && !addPressedLast) {
		m_view->zoom(.5f);
	}
	addPressedLast = addPressedNow;


	m_pos.x = static_cast<int>(m_fPos.x);
	m_pos.y = static_cast<int>(m_fPos.y);

	m_collider->setPos(m_pos);
	// check collision
	if (CollisionLayers::checkAllCollisionsFor(m_collider)) {

		// set the player coor to the collider coor
		m_pos = m_collider->getPos();

		// if there has been a collision, we reset m_fPos to m_pos so we don't have a Mario 64 parallel universes scenario
		m_fPos.x = static_cast<float>(m_pos.x);
		m_fPos.y = static_cast<float>(m_pos.y);
	}

	// set the sprite postion
	m_aTile->setPosition(m_pos);

	// now that all moving is done, move the camera
	if (m_view != nullptr) {
		m_view->setCenter(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y));
	}

	return true;
}
void Player::setCollider(int width, int height) {
	if (m_collider == nullptr) {
		m_collider = new SquareCollider(width, height, m_pos, false);
		CollisionLayers::addCollider(m_collider);
	}
}
void Player::setSprite(sf::Texture * tex) {
	m_aTile = new AliveTile();
	m_aTile->setTexture(tex);
}
}