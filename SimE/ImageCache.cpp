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

void ImageCache::loadTexture(TextureType textureType, const std::string & textureName, const std::string& tilesetName, sf::Texture* in, size_t id) {

	IOUtility::getTexture(textureType, textureName, in);

	if (textureType == SPRITESHEET) {
		spriteSheetTextures[tilesetName] = *in;
	} else {
		tilesets[tilesetName][id] = *in;
	}
}

void ImageCache::loadIndividualTexture(TextureType textureType, const std::string & textureName, sf::Texture * in, size_t id) {

	IOUtility::getTexture(textureType, textureName, in);
	individualSprites[id] = *in;
}

sf::Texture* ImageCache::getTexture(int id, const std::string& setName, bool* needsBounds, sf::IntRect* bounds) {

	if (spriteSheetTilesetBounds[setName].empty()) {
		// the texture is from a tileset made of many images
		return &tilesets[setName][id];
	}
	*needsBounds = true;
	*bounds = spriteSheetTilesetBounds[setName][id];
	return &spriteSheetTextures[setName];
}

sf::Texture* ImageCache::getTexture(int id) {

	return &individualSprites[id];
}


bool ImageCache::loadTileset(const std::string setName) {

	// these are the directories that store tilesets and tilemaps
	const static std::string tilesetPath = "Assets/Textures/Tilesets/";
	const static std::string tilesetFiletype = ".tsx";

	// load the set xml file
	tinyxml2::XMLDocument setXML;
	std::string setLocation = tilesetPath + setName + tilesetFiletype;
	setXML.LoadFile(setLocation.c_str());

	if (setXML.Error() != tinyxml2::XML_SUCCESS) {
		printf("Error: %i\n", setXML.Error());
	}

	// get the root node and the name of the tileset
	const char* tilesetName;
	tinyxml2::XMLNode* rootNode = setXML.FirstChild()->NextSibling();
	rootNode->ToElement()->QueryStringAttribute("name", &tilesetName);

	// get the number of tiles
	int tileCount;
	int columns;
	rootNode->ToElement()->QueryIntAttribute("tilecount", &tileCount);
	rootNode->ToElement()->QueryIntAttribute("columns", &columns);
	if (columns > 0) {

		// tilset is from a spritesheet; there is only one texture listed

		int id = 0;
		int width;
		int height;
		int tileWidth;
		int tileHeight;
		const char* source;

		// get the info for the sprite sheet
		auto image = rootNode->FirstChild();
		image->ToElement()->QueryIntAttribute("width", &width); // the width of the sheet image in pixels
		image->ToElement()->QueryIntAttribute("height", &height); // the height of the sheet image in pixels
		rootNode->ToElement()->QueryIntAttribute("tilewidth", &tileWidth);
		rootNode->ToElement()->QueryIntAttribute("tileheight", &tileHeight);
		image->ToElement()->QueryStringAttribute("source", &source); // the source of the sheet relative to the tileset folder

		/*
		Ok, so TIle has a constructor that takes bounds... so I need to be able to store the bounds in the tileset (within tilesets[setName]
		*/

		//std::string realSource = (std::string) source;
		

		// load the spritesheet texture and add it to the map
		sf::Texture& texture = spriteSheetTextures[setName];
		loadTexture(SPRITESHEET, source, setName, &texture, id);

		int rows = tileCount / columns;
		
		for (int row = 0; row < rows; row++) {
			for (int column = 0; column < columns; column++) {
				spriteSheetTilesetBounds[setName][id].left = column * tileWidth;
				spriteSheetTilesetBounds[setName][id].top = row * tileHeight;
				spriteSheetTilesetBounds[setName][id].width = tileWidth;
				spriteSheetTilesetBounds[setName][id++].height = tileHeight;
			}
		}


	} else {

		// tileset contains many textures

		// load the first tile 
		auto tile = rootNode->FirstChildElement()->NextSibling();
		int id;
		int width;
		int height;
		const char* source;

		// get the info for the first texture
		auto image = tile->FirstChild();
		tile->ToElement()->QueryIntAttribute("id", &id);
		image->ToElement()->QueryIntAttribute("width", &width);
		image->ToElement()->QueryIntAttribute("height", &height);
		image->ToElement()->QueryStringAttribute("source", &source);

		std::string realSource = tilesetPath + (std::string) source;
		//std::string realSource = (std::string) source;

		// prep the first sf::Texture for having its image loaded
		sf::Texture& texture = tilesets[setName][id];
		loadTexture(TILE, source, setName, &texture, id);

		for (int i = 1; i < tileCount; i++) {
			tile = tile->NextSibling();
			tinyxml2::XMLNode* image = tile->FirstChild();
			tile->ToElement()->QueryIntAttribute("id", &id);
			image->ToElement()->QueryIntAttribute("width", &width);
			image->ToElement()->QueryIntAttribute("height", &height);
			image->ToElement()->QueryStringAttribute("source", &source);

			std::string realSource = tilesetPath + (std::string) source;

			sf::Texture& texture = tilesets[tilesetName][id];
			loadTexture(TILE, source, setName, &texture, id);
		}
	}

	printf("Loaded all %d sprites from %s!\n", tileCount, tilesetName);
	return false;
}
bool ImageCache::isSpriteSheet(std::string setName) {

	return !spriteSheetTilesetBounds[setName].empty();
}
}