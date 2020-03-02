#pragma once

#include <SDL.h>
#include <array>
#include "Vector2D.h"

using namespace std;

class HandleEvents
{
private:
	static unique_ptr< HandleEvents> instance_;

	const Uint8* kbState_; //matriz de teclado, para la tecla correspondiente debuelve 1 si esta pulsada y 0 si no
	bool isKeyUp_;
	bool isKeyDown_;
	bool isMouseMotion_;
	bool isMouseButton_;

	Vector2D mousePos_;
	std::array<bool, 3> mbState_;

	//metodos privados para saber que tecla ha sido pulsada

	HandleEvents();
	void clearState();

	inline void onKeyDown(SDL_Event& event) {
		isKeyDown_ = true;
		// kbState_ = SDL_GetKeyboardState(0);
	}
	inline void onKeyUp(SDL_Event& event) {
		isKeyUp_ = true;
		// kbState_ = SDL_GetKeyboardState(0);
	}
	inline void onMouseMotion(SDL_Event& event) {
		isMouseMotion_ = true;
		mousePos_.setVec(Vector2D{ (double)event.motion.x, (double)event.motion.y });
	}
	inline void onMouseButtonChange(SDL_Event& event, bool isDown) {
		isMouseButton_ = true;
		if (event.button.button == SDL_BUTTON_LEFT) {
			mbState_[LEFT] = isDown;
		}
		else if (event.button.button == SDL_BUTTON_MIDDLE) {
			mbState_[MIDDLE] = isDown;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			mbState_[RIGHT] = isDown;
		}
	}

public:
	enum MOUSEBUTTON : Uint8 {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	HandleEvents(HandleEvents&) = delete;
	HandleEvents& operator=(HandleEvents&) = delete;

	virtual ~HandleEvents();

	static HandleEvents* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new HandleEvents());
		}
		return instance_.get();
	}

	// update the state
	void update();

	// keyboard
	inline bool keyDownEvent() {
		return isKeyDown_;
	}

	inline bool keyUpEvent() {
		return isKeyUp_;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		// return kbState_[key] == 1;
		return keyDownEvent() && kbState_[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		// kbState_[key] == 0;
		return keyUpEvent() && kbState_[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	// mouse
	inline bool mouseMotionEvent() {
		return isMouseMotion_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButton_;
	}

	inline const Vector2D& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(MOUSEBUTTON button) {
		return mbState_[button];
	}

};

