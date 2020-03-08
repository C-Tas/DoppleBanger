#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "SDL.h"


class Draw : public GameObject
{
protected:
	Texture* texture_;
	SDL_Rect destiny_ = {0,0,0,0};
	SDL_Rect frame_ = {0,0,0,0};
	Draw() : texture_(nullptr) {};

	Draw(Texture* texture, Point2D pos, Vector2D scale) :
		GameObject(pos, scale), texture_(texture) {
		destiny_.x = (int)pos.getX();
		destiny_.y = (int)pos.getY();
		destiny_.w = (int)scale.getX();
		destiny_.h = (int)scale.getY();
	};

	Draw(Texture* texture, SDL_Rect* frame, Point2D pos, Vector2D scale) :
		GameObject(pos, scale), texture_(texture) {
		destiny_.x = (int)pos.getX();
		destiny_.y = (int)pos.getY();
		destiny_.w = (int)scale.getX();
		destiny_.h = (int)scale.getY();
	};

	Draw(const Draw& other) : GameObject(other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};

	Draw(const Draw&& other)noexcept : GameObject(other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};

	virtual ~Draw() {};//{ delete destiny_, frame_; };

public:
	const virtual void draw() { texture_->render(getDestiny(), SDL_FLIP_NONE); };


#pragma region getters
	const virtual SDL_Rect getDestiny() {
		destiny_.x = (int)pos_.getX();
		destiny_.y = (int)pos_.getY();
		destiny_.w = (int)scale_.getX();
		destiny_.h = (int)scale_.getY();
		return destiny_;
	};
#pragma endregion


#pragma region setters
	void setFrame(SDL_Rect frame) { frame_ = frame; };
	void setDestiny(SDL_Rect destiny) { destiny_ = destiny; };
	void setTexture(Texture* texture) { texture_ = texture; };
#pragma endregion
};
