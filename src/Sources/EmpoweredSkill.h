#pragma once

#include "Skill.h"

class EmpoweredSkill : public Skill
{
private:
	const double COOLDOWN = 6000;	//En milisegundos
	const double MANA_COST = 0.07;	//Porcentaje de mana

public:
	EmpoweredSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) {};
	virtual ~EmpoweredSkill() {};

	virtual void action() {
		double mana = player_->getMaxMana();
		costMana_ = mana * MANA_COST;
		//Si no está en cooldown la habilidad
		if (costMana_ <= player_->getMana() && !skillCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->initEmpowered();
			skillCD_.initCooldown(COOLDOWN);
		}
	};
};

