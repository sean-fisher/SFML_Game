#include "stdafx.h"
#include "Collision.h"
#include <iostream>

//#define DEBUG_MODE
// if you are moving vertically and hit the corner of a square collider, 
// you will be pushed to the right. If this is not defined, the horizontal 
// equivalent will be true. Both cannot be possible right now because the 
// player gets stuck on a corner.
#define SLIDE_VERTICAL

namespace SimE {
SquareCollider::SquareCollider() {

}
SquareCollider::SquareCollider(int width, int height, sf::Vector2i position, bool isStatic) {
	m_position = position;
	m_width = width;
	m_height = height;
	m_isStatic = isStatic;
}

bool SquareCollider::testCollision(Collider* other) {
	static const int roundedEdgeSize = 4;

	int dx = abs(other->getPos().x - m_position.x);
	int dy = abs(other->getPos().y - m_position.y);

	float widthSum = (this->getWidth() / 2.0f + other->getWidth() / 2.0f);
	float heightSum = (this->getHeight() / 2.0f + other->getHeight() / 2.0f);
	//printf("dx: %d, widthSum: %d, dy: %d, heightSum: %d\n", dx, static_cast<int>(widthSum), dy, static_cast<int>(heightSum));
	if (dx < widthSum && dy < heightSum) {
		// Collision!
		static int numCollisions = 0;
		numCollisions++;
		if (this->isStatic()) {
			// we can assume the other collider is not static.
			// we move the other out of the way.


		} else if (other->isStatic()) {
			// we know this one is the only that moves,
			// so we move this out of the way

			float diffY = heightSum - dy;
			float diffX = widthSum - dx;

			if (m_alive && other->getAlive()) {
				m_alive->onCollide(other->getAlive());
			}

			if (diffX > diffY) {
				// move this in the X
				if (m_position.x > other->getPos().x) {
					//  ___|_
					// |	|
					// |	|
					// |____|
					//     |----this

					// if close to the right side, push this right
					int distToEdge = (-m_position.x + other->getPos().x + other->getWidth() / 2);

					int displace;
					if (other->getPos().y < m_position.y) {
						displace = static_cast<int>(other->getPos().y + other->getHeight() / 2.0f + m_height / 2.0f);
					} else {
						displace = static_cast<int>(other->getPos().y - other->getHeight() / 2.0f - m_height / 2.0f);
					}

					if (distToEdge < roundedEdgeSize) {
						setPos(sf::Vector2i(m_position.x + 2, displace));
					} else {
						setPos(sf::Vector2i(m_position.x, displace));
					}
				} else {
					//  _|___
					// |	|
					// |	|
					// |____|
					//  |------this

					// if close to the left side, push this left
					int distToEdge = (m_position.x - other->getPos().x + other->getWidth() / 2);
					int displace;
					if (other->getPos().y < m_position.y) {
						displace = static_cast<int>(other->getPos().y + other->getHeight() / 2.0f + m_height / 2.0f);
					} else {
						displace = static_cast<int>(other->getPos().y - other->getHeight() / 2.0f - m_height / 2.0f);
					}
					if (distToEdge < roundedEdgeSize) {
						setPos(sf::Vector2i(m_position.x - 2, displace));
					} else {
						setPos(sf::Vector2i(m_position.x, displace));
					}
				}

			} else {
				// move this in the Y
				if (m_position.y > other->getPos().y) {
					//      ____
					//     |	|
					//     |	|
					//this-|____|-this
					//

#ifndef SLIDE_VERTICAL
					// if close to the top side, push this up
					int distToEdge = -m_position.y + other->getPos().y + other->getHeight() / 2;
					if (distToEdge < roundedEdgeSize) {
						setPos(sf::Vector2i(m_lastPosition.x, m_position.y + 1));
					} else {
						setPos(sf::Vector2i(m_lastPosition.x, m_position.y));
					}
#else
					m_position = sf::Vector2i(m_lastPosition.x, m_position.y);
#endif
				} else {
					//		 ____
					// this-|	 |-this
					//		|	 |
					//		|____|

#ifndef SLIDE_VERTICAL
					// if close to the bottom side, push this down
					int distToEdge = m_position.y - other->getPos().y + other->getHeight() / 2;
					if (distToEdge < roundedEdgeSize) {
						setPos(sf::Vector2i(m_lastPosition.x, m_position.y - 1));
					} else {
						setPos(sf::Vector2i(m_lastPosition.x, m_position.y));
					}
#else
					m_position = (sf::Vector2i(m_lastPosition.x, m_position.y));
#endif
				}
			}
		} else {
			// both are non-static, so we move both
		}
		return true;
	}

	return false;
}
bool CollisionLayers::checkAllCollisionsFor(Collider* c) {
	CollisionLayers* sCL = singleton();
	bool hasCollided = false;
	for (size_t i = 0; i < sCL->colliders_nonstatic.size(); i++) {
		if (c != sCL->colliders_nonstatic[i]) {
			hasCollided = hasCollided || c->testCollision(sCL->colliders_nonstatic[i]);
		}
	}
	for (size_t i = 0; i < sCL->colliders_static.size(); i++) {
		if (c != sCL->colliders_static[i]) {
			hasCollided = hasCollided || c->testCollision(sCL->colliders_static[i]);
		}
	}
	return hasCollided;
}
void CollisionLayers::addCollider(Collider* c) {
	CollisionLayers* sCL = singleton();
	if (c->isStatic()) {
		sCL->colliders_static.push_back(c);
	} else {
		sCL->colliders_nonstatic.push_back(c);
	}
}
}