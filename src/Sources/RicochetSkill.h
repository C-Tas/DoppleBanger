#pragma once
#include "Skill.h"
class RicochetSkill : public Skill
{
public:
	RicochetSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) { 
		cooldown_ = COOLDOWN;
	};
	~RicochetSkill() {}

	virtual void action() {
		//Si no está en cooldown la habilidad
 		if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			cout << "Rebote" << endl;
			player_->setRicochet(true);
			lastTimeUsed_ = SDL_GetTicks();
		}
	};

private:
	const double COOLDOWN = 5;	//Cooldown de la habilidad
};

