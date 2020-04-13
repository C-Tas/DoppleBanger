#pragma once

#include "Skill.h"

class EmpoweredSkill : public Skill
{
private:
	const int COOLDOWN = 5;
	const double MANA_COST = 10;

public:
	EmpoweredSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; costMana_ = MANA_COST; };
	virtual ~EmpoweredSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
		if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			player_->removeMana(costMana_);
			player_->activateEmpowered();
			lastTimeUsed_ = SDL_GetTicks();
		}
	};
};

