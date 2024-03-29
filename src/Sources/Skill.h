#pragma once

#include "GameManager.h"
#include "Player.h"

enum class SkillBranch { Physical, Distance, Ghost };

class Skill
{

protected:
	Player* player_ = nullptr;
	SkillType type_;
	SkillBranch branch_;
	Cooldown skillCD_;			//Cooldown
	double costMana_ = 0;
public:
	///<summary>Constructora</summary>
	Skill(Player* player, SkillType type, SkillBranch branch) : player_(player), type_(type), branch_(branch) {};

	///<summary>Destructora</summary>
	virtual ~Skill() {};
	///<summary>Método a redefinir en las clases hijas. Define que hace la skill (si es activa) 
	///o los atributos que aumenta (si es pasiva) </summary>
	virtual void action() = 0;

	///<summary>Método para actualizar el cooldown de las skills</summary>
	virtual void update() {
		if (skillCD_.isCooldownActive()) {
			skillCD_.updateCooldown();
		}
	}

	bool isCD() { return skillCD_.isCooldownActive(); };

#pragma region getters
	//<summary>Devuelve si la skill es una pasiva o una activa</summary>
	SkillType getSkillType() { return type_; };
	///<summary>Devuelve a que rama de habilidad pertenece esta skill</summary>
	SkillBranch getSkillBranch() { return branch_; };
#pragma endregion

};