#pragma once
#include <sfml/Graphics.hpp>
#include "Alive.h"

namespace SimE {
class Camera2D : Alive {
public:
	Camera2D(int width, int height, float speed);
	~Camera2D();

	// moves immediately
	void move(int x, int y);
	void moveCenter(int x, int y);

	void goTo(int x, int y);
	void goToCenter(int x, int y);

	void update();
	bool beat() override;

	sf::Vector2i getPosition() { return sf::Vector2i((int) m_fPosition.x, (int)m_fPosition.y); }

	//Helper function for retrieving camera's offset from
	//nearest tile
	sf::Vector2i getTileOffset(int tileSize) { return sf::Vector2i((int)(m_fPosition.x) % tileSize, (int)(m_fPosition.y) % tileSize); }

	sf::IntRect getTileBounds(int tileSize);


private:

	// position of the camera in floats; pixels from origin
	sf::Vector2f m_fPosition;

	sf::Vector2f m_target;

	sf::Vector2i m_size;

	float m_speed; // 0.0 to 1.0
};
}