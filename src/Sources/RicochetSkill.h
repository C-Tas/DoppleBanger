#pragma once
#include "Skill.h"
class RicochetSkill : public Skill
{
private:
	const double COOLDOWN = 5;	//Cooldown de la habilidad
	const double MANA_COST = 10;

public:
	RicochetSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) { cooldown_ = COOLDOWN; costMana_ = MANA_COST; };
	~RicochetSkill() {}

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
 		if ( mana >= costMana_ && ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0))
		{
			player_->removeMana(costMana_);
			player_->setRicochet(true);
			lastTimeUsed_ = SDL_GetTicks();
		}
	};
};

