#include "stdafx.h"
#include "IOUtility.h"

namespace SimE {
IOUtility::IOUtility() {
}


IOUtility::~IOUtility() {
}

int IOUtility::getHashFromFilepath(const std::string & filepath) {
	int hash = 0;
	for (size_t i = 0; i < filepath.length(); i++) {
		hash += filepath[i] * i;
	}
	return hash;
}

bool IOUtility::getTexture(TextureType textureType, const std::string & filepath, sf::Texture* in) {
	switch (textureType) {
	case CHARACTER:
		in->loadFromFile("Assets/Textures/Characters/" + filepath);
		return true;
	case ENEMY:
		in->loadFromFile("Assets/Textures/Enemies/" + filepath);
		return true;
	case TILESET:
		in->loadFromFile("Assets/Textures/Tileset/" + filepath);
		return true;
	case EFFECT:
		in->loadFromFile("Assets/Textures/Effect/" + filepath);
		return true;
	case UI:
		in->loadFromFile("Assets/Textures/UI/" + filepath);
		return true;
	}
}
}