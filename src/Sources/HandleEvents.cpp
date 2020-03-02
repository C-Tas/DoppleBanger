#include "HandleEvents.h"
unique_ptr<HandleEvents> HandleEvents::instance_;

HandleEvents::HandleEvents() {
	clearState();
	kbState_ = SDL_GetKeyboardState(0);
}

HandleEvents::~HandleEvents() {
}

void HandleEvents::update() {

	SDL_Event event;

	clearState();

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;
		}
	}
}

void HandleEvents::clearState() {
	isKeyDown_ = false;
	isKeyUp_ = false;
	isMouseButton_ = false;
	isMouseMotion_ = false;
	for (int i = 0; i < 3; i++) {
		mbState_[i] = false;
	}
}
