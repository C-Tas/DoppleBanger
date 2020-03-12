#include "Texture.h"
#include "Font.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Texture::Texture() : texture_(nullptr), renderer_(nullptr), width_(0), height_(0) {
}

Texture::Texture(SDL_Renderer* renderer, const string& fileName) : texture_(nullptr), width_(0), height_(0) {
	loadFromImg(renderer, fileName);
}

Texture::Texture(SDL_Renderer* renderer, const string& text, const Font* font, const SDL_Color& color) :
	texture_(nullptr), width_(0), height_(0) {
	loadFromText(renderer, text, font, color);
}

Texture::~Texture() {
	close();
}

void Texture::close() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_); // destruye la textura actual
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
	}
}

bool Texture::loadFromImg(SDL_Renderer* renderer, const string& fileName) {
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface != nullptr) {
		close(); // destruye la textura actual para sustituirla
		texture_ = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture_ != nullptr) {
			width_ = surface->w;
			height_ = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	else {
		throw "No se puede cargar la imagen: " + fileName;
	}
	renderer_ = renderer;
	return texture_ != nullptr;
}

bool Texture::loadFromText(SDL_Renderer* renderer, const string& text, const Font* font,
	const SDL_Color& color) {
	SDL_Surface* textSurface = font->renderText(text, color);
	if (textSurface != nullptr) {
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture_ != nullptr) {
			width_ = textSurface->w;
			height_ = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	else {
		throw "No se puede cargar el texto: " + text;
	}
	renderer_ = renderer;
	return texture_ != nullptr;
}

void Texture::render(int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;
	render(dest);
}

void Texture::render(const SDL_Rect& dest, const SDL_Rect& frame) const {
	if (texture_) {
		SDL_RenderCopy(renderer_, texture_, &frame, &dest);
	}
}

void Texture::render(const SDL_Rect& dest) const {
	SDL_Rect frame = { 0, 0, width_, height_ };
	render(dest, frame);
}


void Texture::render(const SDL_Rect& dest, double angle, const SDL_Rect& frame) const {
	if (texture_) {
		SDL_RenderCopyEx(renderer_, texture_, &frame, &dest, angle, nullptr, SDL_FLIP_NONE);
	}
}

void Texture::render(const SDL_Rect& dest, double angle) const {
	SDL_Rect frame = { 0, 0, width_, height_ };
	render(dest, angle, frame);
}
