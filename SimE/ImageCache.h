#pragma once
#include <vector>
#include <map>
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

	void loadTexture(TextureType textureType, const std::string & filepath, sf::Texture* in, size_t id);
	sf::Texture* getTexture(int id);
	bool loadTileset(const std::string setFileName);

private:
	std::map<int, sf::Texture> m_cachedTextureMap;
};

}