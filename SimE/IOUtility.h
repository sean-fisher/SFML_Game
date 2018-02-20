#pragma once

#include <string>
#include <sfml/Graphics.hpp>
#include "MapLayer.h"
#include "enums.h"

namespace SimE {

enum TextureType;

class IOUtility {
public:
	IOUtility();
	~IOUtility();

	static int getHashFromFilepath(const std::string & filepath);
	static bool getTexture(TextureType textureType, const std::string & filepath, sf::Texture* in);
};

}