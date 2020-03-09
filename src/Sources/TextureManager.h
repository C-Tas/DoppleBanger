#pragma once
#include "Texture.h"
#include <map>

//Clase TextureManager de TPV2
class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	// supposed to be called before start using the object
	bool init();

	Texture* getTexture(std::size_t tag){
		return textures_[tag];
	}

	bool loadFromImg(std::size_t, SDL_Renderer* renderer,
		const string& fileName);
	/*
	bool loadFromText(std::size_t, SDL_Renderer* renderer, const string& text,
		const Font* font, const SDL_Color& color);*/
private:
	void storeTexture(std::size_t tag, Texture* texture);

	bool initialized_ = false;
	map<std::size_t, Texture*> textures_;
};

