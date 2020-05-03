#pragma once
#include "Button.h"
#include "HandleEvents.h"
#include "GameManager.h"

class SkillButton: public Button
{
using CallBackOnClickSkill = void(Application * app, SkillButton * button);
using CallBackOnPointerOver = void(Application * app, SkillName skill);
protected:
	///<summary>Bool que marca si la skill está ya asignada o no</summary>
	bool asign_ = false;
	//<summary>Bool que marca si la skill está desbloqueada</summary>
	bool unlocked_ = false;
	///<summary>Si la skill es activa o pasiva</summary>
	SkillType type_;
	///<summary>Callback del boton</summary>
	CallBackOnClickSkill* callbackSkill_ = nullptr;
	///<summary>Callback del boton cuando el cursor está sobre él</summary>
	CallBackOnPointerOver* callbackOnPoint_ = nullptr;
	///<summary>Referencia al handle events</summary>
	HandleEvents* handleEvents_;
	///<summary>identificador de la skill que representa dicho boton</summary>
	SkillName id;

public: 
	///<summary>Constructora de SkillButton</summary>
	SkillButton(Application* app, Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClickSkill* callBack,
		SkillName name, SkillType type, CallBackOnPointerOver* callbackOnPoint);
	///<summary>Destructora</summary>
	virtual ~SkillButton() {};
	virtual bool update();

#pragma region Getters
	bool isAsigned() { return asign_; }
	bool isUnlocked() { return unlocked_; }
	SkillName getSkillId() { return id; }
	SkillType getSkillType() { return type_; }
#pragma endregion

#pragma region Setters
	void setUnlocked(bool state) { unlocked_ = state; }
	void setAsigned(bool state) { asign_ = state; }

#pragma endregion
	
};



