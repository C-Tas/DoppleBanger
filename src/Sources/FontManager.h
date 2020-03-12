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
	FontManager() {};
	virtual ~FontManager();

	bool init();

	///<summary>Devuelve la fuente correspondiente al tag (Resources::FontId::NameTag)</summary>
	Font* getFont(size_t tag) { return fonts_[tag]; };
	///<summary>Carga la fuente pedida</summary>
	bool loadFont(size_t tag, const string& fileName, int size);
};