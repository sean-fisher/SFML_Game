#pragma once
#include <vector>
#include <map>
#include <string>
#include <sfml/Graphics.hpp>

#include "IOUtility.h"
#include "enums.h"

namespace SimE {


class ImageCache {

public:

	static ImageCache* singleton() {
		static ImageCache ic;
		return &ic;
	}

	ImageCache();
	~ImageCache();

	void loadTexture(TextureType textureType, const std::string & textureName, const std::string& tilesetName, sf::Texture* in, size_t id);
	void loadIndividualTexture(TextureType textureType, const std::string & textureName, sf::Texture* in, size_t id);
	sf::Texture* getTexture(int id, const std::string& setName, bool* needsBounds, sf::IntRect* bounds);
	sf::Texture* getTexture(int id);
	bool loadTileset(const std::string setFileName);
	bool isSpriteSheet(std::string setName);

private:
	std::map<int, sf::Texture> individualSprites;
	std::map<std::string, std::map<int, sf::Texture>> tilesets;
	std::map<std::string, std::map<int, sf::IntRect>> spriteSheetTilesetBounds;
	std::map<std::string, sf::Texture> spriteSheetTextures;
};

}