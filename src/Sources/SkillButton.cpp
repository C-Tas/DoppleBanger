#include "SkillButton.h"

SkillButton::SkillButton(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickSkill* callBack, SkillName name, SkillType type, CallBackOnPointerOver* callbackOnPoint) :
	Button(app, texture, pos, scale, nullptr), type_(type) {
	callbackSkill_ = callBack; handleEvents_ = HandleEvents::instance(); id = name;
	callbackOnPoint_ = callbackOnPoint;
	unlocked_ = GameManager::instance()->isSkillUnlocked(name);
	asign_ = GameManager::instance()->isSkillAsign(name);
}

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
