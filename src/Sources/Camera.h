#pragma once

#include <SDL.h>
#include <array>
#include "Vector2D.h"
#include "Application.h"

class Camera
{
private:
	//<summary>impide que haya m�s de un puntero a esta clase</summary>
	static unique_ptr<Camera> instance_;
	SDL_Rect camera_;

	Camera(int width, int height) {
		camera_.x = 0;
		camera_.y = 0;
		camera_.w = width / 2;
		camera_.h = height / 2;
	};

public:
	virtual ~Camera() {};

	//<summary>Crea el handleevents si no existe uno ya</summary>
	static Camera* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new Camera(Application::winWidth_, Application::winHeight_));
		}
		return instance_.get();
	}

	inline void updateCamera(int x, int y)
	{
		camera_.x = x - camera_.w;
		camera_.y = y - camera_.h;
	}

	inline Vector2D getCamera()
	{
		return Vector2D(camera_.x, camera_.y);
	}
};