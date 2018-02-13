#pragma once
#include <vector>
#include <map>
#include <sfml/Graphics.hpp>

namespace SimE {
class ImageCache {
public:
	ImageCache();
	~ImageCache();

	void loadImage(std::string& filepath);
	sf::Image& getImage(int hash);

private:
	std::map<int, sf::Image> m_cachedImageMap;
};

}