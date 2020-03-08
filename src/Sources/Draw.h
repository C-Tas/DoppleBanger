#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "SDL.h"


class Draw : public GameObject
{
protected:
	Texture* texture_;
	SDL_Rect destiny_;
	SDL_Rect frame_;
	Vector2D visPos_;

	Draw() : texture_(nullptr) {};

	Draw(Application* app, Texture* texture, Point2D pos, Vector2D scale) :
		GameObject(app, pos, scale), texture_(texture) {
		destiny_.x = pos.getX();
		destiny_.y = pos.getY();
		destiny_.w = scale.getX();
		destiny_.h = scale.getY();
	};

	Draw(Application* app, Texture* texture, SDL_Rect* frame, Point2D pos, Vector2D scale) :
		GameObject(app, pos, scale), texture_(texture) {
		destiny_.x = pos.getX();
		destiny_.y = pos.getY();
		destiny_.w = scale.getX();
		destiny_.h = scale.getY();
	};

	Draw(const Draw& other) : GameObject(other.app_, other.pos_, other.scale_), 
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};

	Draw(const Draw&& other)noexcept : GameObject(other.app_, other.pos_, other.scale_),
		texture_(other.texture_), destiny_(other.destiny_), frame_(other.frame_) {};

	virtual ~Draw() {};

public:
	const virtual void draw() { texture_->render(getDestiny(), SDL_FLIP_NONE); };

	//Devuelve la posición "visual" del objeto
	//Cuando se mueva un objeto no se mira su posición superior izquierda, sino sus pies.
	void updateVisPos() { visPos_.setVec(Vector2D(pos_.getX() + (scale_.getX() / 2), pos_.getY() + (scale_.getY() * 0.8))); } 

#pragma region getters
	const virtual SDL_Rect getDestiny() {
		destiny_.x = pos_.getX();
		destiny_.y = pos_.getY();
		destiny_.w = scale_.getX();
		destiny_.h = scale_.getY();
		return destiny_;
	};
#pragma endregion


#pragma region setters
	void setFrame(SDL_Rect frame) { frame_ = frame; };
	void setDestiny(SDL_Rect destiny) { destiny_ = destiny; };
	void setTexture(Texture* texture) { texture_ = texture; };
#pragma endregion
};

