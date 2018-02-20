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

bool IOUtility::getTexture(TextureType textureType, const std::string & textureName, sf::Texture* in) {
	switch (textureType) {
	case CHARACTER:
		in->loadFromFile("Assets/Textures/Characters/" + textureName);
		return true;
	case ENEMY:
		in->loadFromFile("Assets/Textures/Enemies/" + textureName);
		return true;
	case TILESET:
		in->loadFromFile("Assets/Textures/Tileset/" + textureName);
		return true;
	case TILE:
		in->loadFromFile("Assets/Textures/Tiles/" + textureName);
		return true;
	case EFFECT:
		in->loadFromFile("Assets/Textures/Effect/" + textureName);
		return true;
	case UI:
		in->loadFromFile("Assets/Textures/UI/" + textureName);
		return true;

	case TEST:
		in->loadFromFile("Assets/Textures/Test/" + textureName);
		return true;
	}
	return false;
}


}