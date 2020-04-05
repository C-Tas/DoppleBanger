#pragma once
#include "Button.h"
#include "HandleEvents.h"
#include "GameManager.h"

class SkillButton: public Button
{
using CallBackOnClickSkill = void(Application * app, SkillButton * button);
protected:
	///<summary>Bool que marca si la skill est� ya asignada o no</summary>
	bool asign_ = false;
	//<summary>Bool que marca si la skill est� desbloqueada</summary>
	bool unlocked_ = false;
	///<summary>Si la skill es activa o pasiva</summary>
	SkillType type_;
	///<summary>Callback del boton</summary>
	CallBackOnClickSkill* callbackSkill_ = nullptr;
	///<summary>Referencia al handle events</summary>
	HandleEvents* handleEvents_;
	///<summary>identificador de la skill que representa dicho boton</summary>
	SkillNames id;

public: 
	///<summary>Constructora de SkillButton</summary>
	SkillButton(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickSkill* callBack, 
		SkillNames name, SkillType type):
		Button(app, texture, pos, scale, nullptr), type_(type) {
		callbackSkill_ = callBack; handleEvents_ = HandleEvents::instance(); id = name;
		unlocked_ = GameManager::instance()->isSkillUnlocked(name);
		asign_ = GameManager::instance()->isSkillAsign(name);
	}
	///<summary>Destructora</summary>
	virtual ~SkillButton() {};
	virtual bool update();

#pragma region Getters
	bool isAsigned() { return asign_; }
	bool isUnlocked() { return unlocked_; }
	SkillNames getSkillId() { return id; }
	SkillType getSkillType() { return type_; }
#pragma endregion

#pragma region Setters
	void setUnlocked(bool state) { unlocked_ = state; }
	void setAsigned(bool state) { asign_ = state; }

#pragma endregion
	
};



