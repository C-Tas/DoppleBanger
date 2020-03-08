#pragma once
#include "GameObject.h"
#include "Texture.h"



class Draw : public GameObject
{
protected:
	Texture* texture_;
	SDL_Rect* destiny_;
	SDL_Rect* frame_;
	Draw() :texture_(nullptr), destiny_(nullptr), frame_(nullptr) {};
	Draw(Texture* texture, SDL_Rect* destiny, Point2D pos, Vector2D scale) :
		GameObject(pos, scale), texture_(texture), destiny_(destiny), frame_(nullptr) {};
	Draw(Texture* texture, SDL_Rect* destiny, SDL_Rect* frame, Point2D pos, Vector2D scale) :
		GameObject(pos, scale), frame_(frame), texture_(texture), destiny_(destiny) {};
	Draw(const Draw& other) : GameObject(other.pos_, other.scale_), 
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};
	Draw(const Draw&& other)noexcept : GameObject(other.pos_, other.scale_),	
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};
	virtual ~Draw() { delete destiny_, frame_; };
public:
	const virtual void draw() { texture_->render(*destiny_, SDL_FLIP_NONE); };
#pragma region getters
	const virtual SDL_Rect getDestiny() { return *destiny_; };
#pragma endregion

#pragma region setters
	void setFrame(SDL_Rect* frame) { frame_ = frame; };
	void setDestiny(SDL_Rect* destiny) { destiny_ = destiny; };
	void setTexture(Texture* texture) { texture_ = texture; };
#pragma endregion
};

