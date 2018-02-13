#pragma once

#include <string>
#include <sfml/Graphics.hpp>

namespace SimE {
enum TextureType {
	CHARACTER,
	ENEMY,
	TILESET,
	EFFECT,
	UI
};
class IOUtility {
public:
	IOUtility();
	~IOUtility();

	static int getHashFromFilepath(const std::string & filepath);
	static bool getTexture(TextureType textureType, const std::string & filepath, sf::Texture* in);
};

}