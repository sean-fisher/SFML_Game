#include "stdafx.h"
#include "ImageCache.h"
#include "IOUtility.h"

namespace SimE {
ImageCache::ImageCache() {
}


ImageCache::~ImageCache() {
}

void ImageCache::loadImage(std::string& filepath) {

	m_cachedImageMap[IOUtility::getHashFromFilepath(filepath)];
}

sf::Image & ImageCache::getImage(int hash) {
	return m_cachedImageMap[hash];
}
}