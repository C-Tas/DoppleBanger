#pragma once

#include "Skill.h"
#include "HandleEvents.h"

class ClonSkill : public Skill
{
private:
	const int COOLDOWN = 5;
	const int CLON_SPAWN_RANGE = 700;

public:
	ClonSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; };
	virtual ~ClonSkill() {};

	virtual void action() {
		//Si no está en cooldown la habilidad
		if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			cout << "\nClon\n";
			Vector2D dist = Vector2D(HandleEvents::instance()->getMousePos().getX() - player_->getPos().getX(), HandleEvents::instance()->getMousePos().getY() - player_->getPos().getY());
			if (dist.magnitude() <= CLON_SPAWN_RANGE)
			{
				player_->createClon();
				lastTimeUsed_ = SDL_GetTicks();
			}
		}
	};
};