#include "SkillButton.h"

bool SkillButton::update()
{
	SDL_Point mouse = { handleEvents_->getMousePos().getX(), handleEvents_->getMousePos().getY() };

	if (unlocked_ && SDL_PointInRect(&mouse, &getDestiny()) && handleEvents_->getMouseButtonState(HandleEvents::MOUSEBUTTON::LEFT)) {
		callbackSkill_(app_, this);
		return true;
	}
	return false;
}
