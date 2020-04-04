#pragma once
#include "Button.h"
#include "HandleEvents.h"

class SkillButton: public Button
{
using CallBackOnClickSkill = void(Application * app, SkillButton * button);
protected:
	bool asign_ = false;
	bool unlocked_ = false;
	CallBackOnClickSkill* callbackSkill_ = nullptr;
	HandleEvents* handleEvents_;

public: 
	SkillButton(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickSkill* callBack):
		Button(app, texture, pos, scale, nullptr) {
		callbackSkill_ = callBack; handleEvents_ = HandleEvents::instance();
	}

	virtual ~SkillButton() {};
	virtual bool update();

#pragma region Getters
	bool isAsigned() { return asign_; }
	bool isUnlocked() { return unlocked_; }
#pragma endregion

#pragma region Setters
	void setUnlocked(bool state) { unlocked_ = state; }
	void setAsigned(bool state) { asign_ = state; }

#pragma endregion
	
};



