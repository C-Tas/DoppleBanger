#pragma once

#include "SDL.h"
#include "SDL_image.h" 

#include <string>

using namespace std;
typedef unsigned int uint;

class Texture {
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint w = 0;	//Ancho de la imagen
	uint h = 0;	//Alto de la imagen
	uint fw = 0; // Ancho del frame
	uint fh = 0; // Alto del frame
	uint numCols = 1; //Número de columnas de la imagen
	uint numRows = 1; //Número de filas de la imagen

public:
	Texture(SDL_Renderer* r) : renderer(r) {}
	Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename, numRows, numCols); }
	~Texture() { cls(); }
	void cls();

	int getW() const { return w; };
	int getH() const { return h; };
	uint getNumRows() const { return numRows; }
	uint getNumCols() const { return numCols; }
	SDL_Texture* getTexture() const { return texture; }

	void load(string filename, uint numRows = 1, uint numCols = 1);
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

