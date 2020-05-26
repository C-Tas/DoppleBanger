#pragma once

#include "Skill.h"

class EmpoweredSkill : public Skill
{
private:
	const double COOLDOWN = 10000;	//En milisegundos
	const double MANA_COST = 10;

public:
	EmpoweredSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { costMana_ = MANA_COST; };
	virtual ~EmpoweredSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
		if (mana >= costMana_ && !skillCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->initEmpowered();
			skillCD_.initCooldown(COOLDOWN);
		}
	};
};

