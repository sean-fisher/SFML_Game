#include "stdafx.h"
#include "ImageCache.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>

namespace SimE {
ImageCache::ImageCache() {
}


ImageCache::~ImageCache() {
}

void ImageCache::loadTexture(TextureType textureType, const std::string & filepath, sf::Texture* in, size_t id) {
	IOUtility::getTexture(textureType, filepath, in);
	m_cachedTextureMap[id] = *in;
}

sf::Texture* ImageCache::getTexture(int id) {



	return &m_cachedTextureMap[id];
}

bool ImageCache::loadTileset(const std::string mapName) {

	// these are the directories that store tilesets and tilemaps
	const static std::string tilesetPath = "Assets/Textures/Tilesets/";
	const static std::string tilesetFiletype = ".tsx";

	// load the set xml file
	tinyxml2::XMLDocument mapXML;
	std::string mapLocation = tilesetPath + mapName + tilesetFiletype;
	mapXML.LoadFile(mapLocation.c_str());

	if (mapXML.Error() != tinyxml2::XML_SUCCESS) {
		printf("Error: %i\n", mapXML.Error());
	}

	// get the root node and the name of the tileset
	const char* tilesetName;
	tinyxml2::XMLNode* rootNode = mapXML.FirstChild()->NextSibling();
	rootNode->ToElement()->QueryStringAttribute("name", &tilesetName);

	// get the number of tiles
	int tileCount;
	rootNode->ToElement()->QueryIntAttribute("tilecount", &tileCount);

	// load the first tile 
	auto tile = rootNode->FirstChildElement()->NextSibling();
	int id;
	int width;
	int height;
	const char* source;
	auto image = tile->FirstChild();
	tile->ToElement()->QueryIntAttribute("id", &id);
	image->ToElement()->QueryIntAttribute("width", &width);
	image->ToElement()->QueryIntAttribute("height", &height);
	image->ToElement()->QueryStringAttribute("source", &source);

	//std::string realSource = tilesetPath + (std::string) source;
	std::string realSource = (std::string) source;

	// prep the first sf::Texture for having its image loaded
	sf::Texture& texture = m_cachedTextureMap[id];
	loadTexture(TILE, source, &texture, id);

	for (int i = 1; i < tileCount; i++) {
		tile = tile->NextSibling();
		tinyxml2::XMLNode* image = tile->FirstChild();
		tile->ToElement()->QueryIntAttribute("id", &id);
		image->ToElement()->QueryIntAttribute("width", &width);
		image->ToElement()->QueryIntAttribute("height", &height);
		image->ToElement()->QueryStringAttribute("source", &source);

		realSource = (std::string) source;

		sf::Texture& texture = m_cachedTextureMap[id];
		loadTexture(TILE, source, &texture, id);
	}
	printf("Loaded all %d sprites from %s!\n", tileCount, tilesetName);
	return false;
}/*
bool ImageCache::loadTilemapLayerFromCSV(const std::string mapFileName, MapLayer * mapLayer) {

	const static std::string tilemapPath = "Assets/Tilemaps/";
	const static std::string tilemapFiletype = ".csv"; // entire maps are stored in .tmx. I can also store layers separately as .csv

	std::string fullPath = tilemapPath + mapFileName + tilemapFiletype;

	std::ifstream file(fullPath, std::ifstream::in);
	if (file.fail()) {
		perror(fullPath.c_str());
		return false;
	}
	char character;
	std::string value;
	int x = 0, y = 0, sum = 0; // x and y represent tile coordinates, so we only change them when new tiles are added
	while (file >> std::noskipws >> character) {
		if (character != ',') {
			if (character == '\n') {
				// EoL reached; add the last tile of the row
				int id = std::stoi(value);
				if (id != -1) {
					sf::Texture* tex = &m_cachedTextureMap[id];
					mapLayer->addTile(x, y, tex);
					sum++;
				}
				value = "";
				y++;
				x = 0;
			} else {
				// form a string that represents the int value of a tile
				value += character;
			}
		} else {
			// the end of the value has been found; add the value to the buffer
			int id = std::stoi(value);
			if (id != -1) {
				sf::Texture* tex = &m_cachedTextureMap[id];
				mapLayer->addTile(x, y, tex);
				sum++;
			}
			value = "";
			x++;
		}
	}
	printf("Read tile map layer of size %d", sum);
	file.close();

	return true;
}*/
}