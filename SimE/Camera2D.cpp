#include "stdafx.h"
#include "Camera2D.h"
#include "Timer.h"

namespace SimE {

Camera2D::Camera2D(int width, int height, float speed) {

	m_size.x = width;
	m_size.y = height;

	if (speed < 0.0f) speed = 0.0f;
	if (speed > 1.0f) speed = 1.0f;

	this->m_speed = speed;
}

Camera2D::~Camera2D() {
}
void Camera2D::move(int x, int y) {

	m_fPosition.x = (float)x;
	m_fPosition.y = (float)y;
	m_target.x = (float)x;
	m_target.y = (float)y;
}
void Camera2D::moveCenter(int x, int y) {
	x -= m_size.x / 2;
	y -= m_size.y / 2;

	m_fPosition.x = (float)x;
	m_fPosition.y = (float)y;
	m_target.x = (float)x;
	m_target.y = (float)y;
}

// sets target to coor
void Camera2D::goTo(int x, int y) {
	m_target.x = (float)x;
	m_target.y = (float)y;
}

// centers target at coordinates
void Camera2D::goToCenter(int x, int y) {
	x -= m_size.x / 2;
	y -= m_size.y / 2;
	m_target.x = (float)x;
	m_target.y = (float)y;
}
void Camera2D::update() {
	float x, y, distance;

	float dx, dy, velocity;

	x = (float)(m_target.x - m_fPosition.x);
	y = (float)(m_target.y - m_fPosition.y);

	//If we're within 1 pixel of the target already, just snap
	if ((x*x + y*y) <= 1) {
		m_fPosition.x = m_target.x;
		m_fPosition.y = m_target.y;
	} else {

		distance = sqrt(x * x + y * y);
		velocity = distance * m_speed / Timer::delta();

		if (velocity < 1.0f) velocity = 1.0f;

		dx = x * velocity / distance; // m * m/s / m = m/s
		dy = y * velocity / distance; // m * m/s / m = m/s

		m_fPosition.x += dx;
		m_fPosition.y += dy;
	}

}
bool Camera2D::beat() {
	update();
	return true;
}
sf::IntRect Camera2D::getTileBounds(int tileSize) {

	int x = (int)(m_fPosition.x / tileSize);
	int y = (int)(m_fPosition.y / tileSize);

	int width = (int)(m_size.x / tileSize + 2);
	int height = (int)(m_size.y / tileSize + 2);

	if (x % tileSize != 0) width++;
	if (y % tileSize != 0) height++;

	return sf::IntRect(x, y, width, height);
}
}