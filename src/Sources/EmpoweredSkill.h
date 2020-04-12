#pragma once

#include "Skill.h"

class EmpoweredSkill : public Skill
{
private:
	const int COOLDOWN = 5;

public:
	EmpoweredSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; };
	virtual ~EmpoweredSkill() {};

	virtual void action() {
		//Si no est� en cooldown la habilidad
		if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			player_->activateEmpowered();
			lastTimeUsed_ = SDL_GetTicks();
		}
	};
};

