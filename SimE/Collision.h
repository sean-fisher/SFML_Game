#pragma once

#include <vector>
#include <sfml/Graphics.hpp>

#include "Alive.h"

namespace SimE {


class Collider {
public:
	virtual bool testCollision(Collider* other) = 0;

	int getWidth() { 
		return m_width; 
	}
	int getHeight() { 
		return m_height; 
	}
	sf::Vector2i getPos() { 
		return m_position; 
	}
	sf::Vector2i getLastPos() { 
		return m_lastPosition; 
	}
	bool isStatic() { 
		return m_isStatic; 
	}
	Alive* getAlive() { 
		return m_alive; 
	}

	void setWidth(int width) { m_width = width; }
	void setHeight(int height) { m_height = height; }
	void setPos(sf::Vector2i position) {
		m_position = position;
	}
	void setLastPos(sf::Vector2i position) { m_lastPosition = position; }
	void setStatic(bool is_static) { m_isStatic = is_static; }
	void setAlive(Alive* alive) { m_alive = alive; }

protected:
	bool m_isStatic;
	int m_width;
	int m_height;
	sf::Vector2i m_position;
	sf::Vector2i m_lastPosition;
	Alive* m_alive;
};

class SquareCollider : public Collider {
	//	 _______
	//	|		|			x is the center
	//	|   x	|height
	//	|_______|
	//	  width
public:

	bool testCollision(Collider* other) override;

	SquareCollider();
	SquareCollider(int width, int height, sf::Vector2i position, bool isStatic);

};

class CollisionLayers {
public:
	static bool checkAllCollisionsFor(Collider* c);
	static void addCollider(Collider*);
	static CollisionLayers* singleton() {
		static CollisionLayers singleton;
		return &singleton;
	}
private:


	std::vector<Collider*> colliders_nonstatic;
	std::vector<Collider*> colliders_static;

};
}