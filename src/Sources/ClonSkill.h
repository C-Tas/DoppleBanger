#pragma once

#include "Skill.h"
#include "CollisionCtrl.h"

class ClonSkill : public Skill
{
private:
	const int COOLDOWN = 5;
	const int CLON_SPAWN_RANGE = 1000;

public:
	ClonSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; };
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
				player_->createClon();
				lastTimeUsed_ = SDL_GetTicks();
				player_->setClonCoolDown();
				GameManager::instance()->setSkillCooldown(true, SkillKey::R);
			}
		}
	};
};