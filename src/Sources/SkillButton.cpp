#include "SkillButton.h"

bool SkillButton::update()
{
	SDL_Point mouse = { handleEvents_->getRealMousePos().getX(), handleEvents_->getRealMousePos().getY() };

	if (unlocked_ && SDL_PointInRect(&mouse, &getDestiny()) && handleEvents_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		callbackSkill_(app_, this);
		return true;
	}
	else if (SDL_PointInRect(&mouse, &getDestiny())) {
		callbackOnPoint_(app_, id);
		return false;
	}
	return false;
}
