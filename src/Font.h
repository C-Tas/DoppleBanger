#pragma once
#include <SDL_ttf.h>
#include <string>
using namespace std;

class Font {
private:
	TTF_Font* font_;

public:
	Font() : font_(nullptr) {};
	Font(const string& fileName, int size) { load(fileName, size); };
	virtual ~Font() { close(); };

	bool load(const string& fileName, int size);
	void close();
	SDL_Surface* renderText(const string& text, SDL_Color color) const;
};

