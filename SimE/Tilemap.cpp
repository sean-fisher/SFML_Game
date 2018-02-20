#include "stdafx.h"
#include "Tilemap.h"
#include <boost/filesystem.hpp>
#include <cstdarg>
#include "tinyxml2.h"

namespace SimE {

const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

// from http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
struct path_leaf_string {
	std::string operator()(const boost::filesystem::directory_entry& entry) const {
		return entry.path().leaf().string();
	}
};

void read_directory(const std::string& name, std::vector<std::string> &v) {
	boost::filesystem::path p(name);
	boost::filesystem::directory_iterator start(p);
	boost::filesystem::directory_iterator end;
	std::transform(start, end, std::back_inserter(v), path_leaf_string());
}// end of cited section


Tilemap::Tilemap(int width, int height, std::string mapName, ImageCache* imageCache, bool isXML, std::vector<int> layersToSkip) {
	m_imageCache = imageCache;
	if (!isXML) {
		loadAllLayers(width, height, mapName, layersToSkip);
	} else {
		loadTilemapFromTMX(mapName, imageCache, layersToSkip);
	}
}

void Tilemap::loadAllLayers(int width, int height, std::string mapName, std::vector<int> layersToSkip) {
	std::string directory = "Assets/Tilemaps";
	std::vector<std::string> filenames;

	// find all the files in the target directory
	read_directory(directory, filenames);


	std::vector<std::string> relevantFilenames;
	// find the files with given map name.
	// this way we can get all the separate layers.
	for (size_t i = 0; i < filenames.size(); i++) {
		bool one = filenames[i].find(mapName) != std::string::npos;
		bool two = filenames[i].find(".csv") != std::string::npos;
		if (one && two) {
			relevantFilenames.push_back(filenames[i]);
		}
	}

	// read each layer into a sprite batch
	for (size_t i = 0; i < relevantFilenames.size(); i++) {
		if (std::find(layersToSkip.begin(), layersToSkip.end(), i) == layersToSkip.end()) {
			std::cout << "Loaded Level Data: " << relevantFilenames[i] << std::endl;
			MapLayer* in = new MapLayer(width, height);

			loadTilemapLayerFromCSV(relevantFilenames[i], m_imageCache, in);
			m_layers.push_back(in);
		}
	}

}

void Tilemap::addAliveTileToLayer(AliveTile * aTile, int layer) {
	m_layers[layer]->addTile(aTile);
}

void Tilemap::drawAll(sf::RenderWindow* renderWindow, sf::Vector2f center, sf::Vector2f bounds) {
	MapLayer* currLayer;
	for (int i = 0; i < m_layers.size(); i++) {
		currLayer = m_layers[i];
		if (currLayer != nullptr) {
			currLayer->draw(renderWindow, center, bounds);
		}
	}
	/*
	if (debugMode == 1) {

		for (int i = 0; i < entireMap.size(); i++) {
			currentLayer = entireMap[i];
			if (currentLayer != nullptr) {
				currentLayer->draw(renderWindow, center, bounds);
			}
		}
	}*/
}

bool Tilemap::loadTilemapLayerFromCSV(const std::string mapFileName, ImageCache* imageCache, MapLayer* in) {

	const static std::string tilemapPath = "Assets/Tilemaps/";
	const static std::string tilemapFiletype = ".csv"; // entire maps are stored in .tmx. I can also store layers separately as .csv

	std::string fullPath = tilemapPath + mapFileName;// +tilemapFiletype;

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
					sf::Texture* tex = imageCache->getTexture(id);//&m_cachedTextureMap[id];

					// figure out the rotation/mirror of the tile
					bool flipped_horizontally = (id & FLIPPED_HORIZONTALLY_FLAG);
					bool flipped_vertically = (id & FLIPPED_VERTICALLY_FLAG);
					bool flipped_diagonally = (id & FLIPPED_DIAGONALLY_FLAG);

					float scaleX = flipped_horizontally ? -1 : 1;
					float scaleY = flipped_vertically ? -1 : 1;

					in->addTile(x, y, tex, scaleX, scaleY, flipped_diagonally);
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

				// figure out the rotation/mirror of the tile
				bool flipped_horizontally = (id & FLIPPED_HORIZONTALLY_FLAG);
				bool flipped_vertically = (id & FLIPPED_VERTICALLY_FLAG);
				bool flipped_diagonally = (id & FLIPPED_DIAGONALLY_FLAG);
				
				float scaleX = flipped_horizontally ? -1 : 1;
				float scaleY = flipped_vertically ? -1 : 1;

				static int tile = 0;
				sf::Texture* tex = imageCache->getTexture(id); //&m_cachedTextureMap[id];
				in->addTile(x, y, tex, scaleX, scaleY, flipped_diagonally);
				sum++;
			}
			value = "";
			x++;
		}
	}
	printf("Read tile map layer of size %d", sum);
	file.close();

	return true;
}
bool Tilemap::loadTilemapFromTMX(const std::string mapFileName, ImageCache* imageCache, std::vector<int> layersToSkip) {

	const static std::string tilemapPath = "Assets/Tilemaps/";
	const static std::string tilemapFiletype = ".tmx"; // entire maps are stored in .tmx. I can also store layers separately as .csv


	// load the map xml file
	tinyxml2::XMLDocument mapXML;
	std::string mapLocation = tilemapPath + mapFileName + tilemapFiletype;
	mapXML.LoadFile(mapLocation.c_str());

	if (mapXML.Error() != tinyxml2::XML_SUCCESS) {
		printf("Error: %i\n", mapXML.Error());
	}

	int width;
	int height;
	int tileWidth;
	int tileHeight;
	// get the root node and the name of the tileset
	tinyxml2::XMLNode* rootNode = mapXML.FirstChild()->NextSibling();
	rootNode->ToElement()->QueryIntAttribute("width", &width);
	rootNode->ToElement()->QueryIntAttribute("height", &height);
	rootNode->ToElement()->QueryIntAttribute("tilewidth", &tileWidth);
	rootNode->ToElement()->QueryIntAttribute("tileheight", &tileHeight);
	
	tinyxml2::XMLNode* layerElement = rootNode->FirstChildElement()->NextSibling();

	std::string value;
	int layerNum = 0; // number of layers added
	int layersChecked = 0; // the numbers of the layer being checked; not all may be added
	while (layerElement != nullptr) {
		int x = 0, y = 0, sum = 0; // x and y represent tile coordinates, so we only change them when new tiles are added

		if (std::find(layersToSkip.begin(), layersToSkip.end(), layersChecked) == layersToSkip.end()) {
			if (layerNum >= m_layers.size()) {
				m_layers.push_back(new MapLayer(width, height));
			}

			// load csv data

			// skip over the tileset entries
			while (layerElement->FirstChild() == nullptr) {
				layerElement = layerElement->NextSibling();
			}
			const char* csvLayer = layerElement->FirstChild()->ToElement()->GetText();

			int charIndex = 1;// we skip the first character because it is '\0'
			char character = csvLayer[charIndex];
			while (character != '\0') {
				if (character != ',') {
					if (character == '\n') {
						// EoL reached; add the last tile of the row
						if (value != "") {
							unsigned long fullid = std::stoul(value);
							if (fullid != -1 && fullid != 0) {

								// figure out the rotation/mirror of the tile
								bool flipped_horizontally = (fullid & FLIPPED_HORIZONTALLY_FLAG);
								bool flipped_vertically = (fullid & FLIPPED_VERTICALLY_FLAG);
								bool flipped_diagonally = (fullid & FLIPPED_DIAGONALLY_FLAG);

								int id = (fullid & ~(FLIPPED_HORIZONTALLY_FLAG |
									FLIPPED_VERTICALLY_FLAG |
									FLIPPED_DIAGONALLY_FLAG)) - 1; // minus one because the tileset starts at 0 but the map has 0 as empty

								float scaleX = flipped_horizontally ? -1 : 1;
								float scaleY = flipped_vertically ? -1 : 1;

								sf::Texture* tex = imageCache->getTexture(id);//&m_cachedTextureMap[id];
								m_layers[layerNum]->addTile(x, y, tex, scaleX, scaleY, flipped_diagonally);
								sum++;
							}
							value = "";
						}
						y++;
						x = 0;
					} else {
						// form a string that represents the int value of a tile
						value += character;
					}
				} else {
					// the end of the value has been found; add the value to the buffer
					if (value != "") {
						unsigned long fullid = std::stoul(value);
						if (fullid != -1 && fullid != 0) {
							int id = (fullid & ~(FLIPPED_HORIZONTALLY_FLAG |
								FLIPPED_VERTICALLY_FLAG |
								FLIPPED_DIAGONALLY_FLAG)) - 1; // minus one because the tileset starts at 0 but the map has 0 as empty;

							// figure out the rotation/mirror of the tile
							bool flipped_horizontally = (fullid & FLIPPED_HORIZONTALLY_FLAG);
							bool flipped_vertically = (fullid & FLIPPED_VERTICALLY_FLAG);
							bool flipped_diagonally = (fullid & FLIPPED_DIAGONALLY_FLAG);

							float scaleX = flipped_horizontally ? -1 : 1;
							float scaleY = flipped_vertically ? -1 : 1;
							int rotDegrees = flipped_diagonally ? 90 : 0;

							static int tile = 0;
							sf::Texture* tex = imageCache->getTexture(id); //&m_cachedTextureMap[id];
							m_layers[layerNum]->addTile(x, y, tex, scaleX, scaleY, flipped_diagonally);
							sum++;
						}
						value = "";
					}
					x++;
				}
				character = csvLayer[++charIndex];
			}
			layerNum++;
		}
		layersChecked++;
		layerElement = layerElement->NextSibling();
	}

	return true;
}
}
