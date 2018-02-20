#pragma once

#include <vector>
#include <algorithm> // for for_each
#include <sfml/Graphics.hpp>

namespace SimE {
class Alive {
public:
	Alive();
	~Alive();

	static void beatAll();

	virtual bool beat() { return true; }
	virtual bool onCollide(Alive* other) { return true; }

	// must be called in order for beat to start being automatically called
	bool birth();

	void setPos(int x, int y) { m_pos.x = x; m_pos.y = y; }
	sf::Vector2i getPos() { return m_pos; }

	virtual void setSprite(sf::Sprite* sprite) { m_sprite = sprite; }
	virtual void setSprite(sf::Texture* tex);

private:
	static std::vector<Alive*> m_sAllAlive;


protected:
	sf::Vector2i m_pos;
	sf::Sprite* m_sprite;
};

}