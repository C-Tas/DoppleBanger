#pragma once
#include "Font.h"
#include <string>
#include <map>
using namespace std;

class FontManager {
private:
	map<int, Font*> fonts_;
	bool initialized_ = false;
public:
	FontManager() : initialized_(false) {};
	virtual ~FontManager();

	bool init();

	Font* getFont(size_t tag);
	bool loadFont(size_t tag, const string& fileName, int size);
};