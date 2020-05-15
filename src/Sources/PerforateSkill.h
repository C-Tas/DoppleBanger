#pragma once
#include "Skill.h"
class PerforateSkill : public Skill
{
private:
	const int COOLDOWN = 2; //En segundos
	const double MANA_COST = 10;

public:
	PerforateSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) { cooldown_ = COOLDOWN; costMana_ = MANA_COST; };
	~PerforateSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
		if (mana >= costMana_ && ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0))
		{
			player_->removeMana(costMana_);
			player_->setPerforate(true);
			lastTimeUsed_ = SDL_GetTicks();
		}
	};
};