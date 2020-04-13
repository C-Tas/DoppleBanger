#pragma once

#include "Skill.h"
#include "HandleEvents.h"

class ClonSkill : public Skill
{
private:
	const int COOLDOWN = 5;
	const int CLON_SPAWN_RANGE = 700;
	const double MANA_COST = 10;

public:
	ClonSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; costMana_ = MANA_COST; };
	virtual ~ClonSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
		if (costMana_ <= mana && (SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			cout << "\nClon\n";
			Vector2D dist = Vector2D(HandleEvents::instance()->getRelativeMousePos().getX() - player_->getPos().getX(), HandleEvents::instance()->getRelativeMousePos().getY() - player_->getPos().getY());
			if (dist.magnitude() <= CLON_SPAWN_RANGE)
			{
				player_->removeMana(costMana_);
				cout << "Baja maná" << endl;
				player_->createClon();
				lastTimeUsed_ = SDL_GetTicks();
				player_->setClonCoolDown();
				GameManager::instance()->setSkillCooldown(true, Key::R);
			}
		}
	};
};