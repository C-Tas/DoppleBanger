#pragma once
#include "Skill.h"
class PerforateSkill : public Skill
{
public:
	PerforateSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) { cooldown_ = COOLDOWN; };
	~PerforateSkill() {};

	virtual void action() {
		//Si no está en cooldown la habilidad
		if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			cout << "Perforante" << endl;
			player_->setPerforate(true);
			lastTimeUsed_ = SDL_GetTicks();
		}
	};

private:
	const int COOLDOWN = 2; //En segundos
};