#pragma once

#include <SDL.h>
#include "Vector2D.h"
#include "Camera.h"

using namespace std;

class HandleEvents
{
private:
    //<summary>impide que haya más de un puntero a esta clase</summary>
	static unique_ptr<HandleEvents> instance_;

	const Uint8* kbState_; //matriz de teclado, para la tecla correspondiente debuelve 1 si esta pulsada y 0 si no
	//<summary>booleano de si la tecla esta soltada</summary>
	bool isKeyUp_;
	//<summary>booleano de si la tecla esta pulsada</summary>
	bool isKeyDown_;
	//<summary>booleano de si el raton esta en movimiento</summary>
	bool isMouseMotion_;
	//<summary>booleano de si el raton esta pulsado</summary>
	bool isMouseButton_;
    //<summary>Vector con la posicion del raton</summary>
	Vector2D mousePos_;
	//<summary>array con los 3 botones del raton</summary>
	std::array<bool, 3> mbState_;

	//metodos privados para saber que tecla ha sido pulsada
	//<summary>Constructor de HandleEvents</summary>
	HandleEvents();
	//<summary>devuelve todos los booleanos a falsos</summary>
	void clearState();
	//<summary>Establece que la tecla esta pulsada</summary>
	inline void onKeyDown(SDL_Event& event) {
		isKeyDown_ = true;
	}
	//<summary>establece que la tecla fue soltada</summary>
	inline void onKeyUp(SDL_Event& event) {
		isKeyUp_ = true;
	}
	//<summary>Establece la nueva posicion del raton</summary>
	inline void onMouseMotion(SDL_Event& event) {
		isMouseMotion_ = true;
		mousePos_.setVec(Vector2D{ (double)event.motion.x, (double)event.motion.y });
	}
	//<summary>Establece que boton del mause fue pulsado</summary>
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
	//<summary>enum para diferenciar los botones del raton</summary>
	enum  MOUSEBUTTON : Uint8 {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	//<summary>inhibir constructor por copia</summary>
	HandleEvents(HandleEvents&) = delete;
	//<summary>inhibir operador de asignacion</summary>
	HandleEvents& operator=(HandleEvents&) = delete;

	//<summary>Destructor del handleevents</summary>
	virtual ~HandleEvents();

	//<summary>Crea el handleevents si no existe uno ya</summary>
	static HandleEvents* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new HandleEvents());
		}
		return instance_.get();
	}

	
	//<summary>Se tratan los distintos eventos</summary>
	void update();

	// keyboard
	#pragma region Keyboard
    //<summary>Devuelve si esta pulsada</summary>
	inline bool keyDownEvent() {
		return isKeyDown_;
	}

	//<summary>Devuelve el booleano de si esta o no esta soltada</summary>
	inline bool keyUpEvent() {
		return isKeyUp_;
	}

	//<summary>Devuelve si la tecla ha sido pulsada</summary>
	inline bool isKeyDown(SDL_Scancode key) {
		// return kbState_[key] == 1;
		return keyDownEvent() && kbState_[key] == 1;
	}

	//<summary>Devuelve si la tecla ha sido pulsada</summary>
	inline bool isKeyDown(SDL_Keycode key) {
		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	//<summary>Devuelve si la tecla ha sido soltada</summary>
	inline bool isKeyUp(SDL_Scancode key) {
		// kbState_[key] == 0;
		return keyUpEvent() && kbState_[key] == 0;
	}

	//<summary>Devuelve si la tecla ha sido soltada</summary>
	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}
    #pragma endregion
    #pragma region Mouse

	//<summary>Devuelve si el raton esta en movimiento</summary>
	inline bool mouseMotionEvent() {
		return isMouseMotion_;
	}

	//<summary>Devuelve si el raton esta presionado</summary>
	inline bool mouseButtonEvent() {
		return isMouseButton_;
	}

	//<summary>devuelve la posicion del raton</summary>
	inline const Vector2D& getRealMousePos() {
		return mousePos_;
	}

	//<summary>devuelve la posicion del raton</summary>
	inline const Vector2D getRelativeMousePos() {
		Vector2D pos = mousePos_;
		pos.setX(pos.getX() + Camera::instance()->getCamera().getX());
		pos.setY(pos.getY() + Camera::instance()->getCamera().getY());
		return pos;
	}

	//<summary>devuelve el estado del boton que le pases por paremtro</summary>
	inline bool getMouseButtonState(MOUSEBUTTON button) {
		return mbState_[button];
	}

	//<summary>devuelve el estado del boton que le pases por paremtro</summary>
	inline int getMouseButtonState(int button) { //No s� usar el MOUSEBUTTON xD
		return mbState_[button];
	}
	#pragma endregion
};

