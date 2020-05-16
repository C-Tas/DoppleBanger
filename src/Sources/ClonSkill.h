#pragma once

#include "Skill.h"
#include "CollisionCtrl.h"

class ClonSkill : public Skill
{
private:
	const double COOLDOWN = 10000;	//En milisegundos
	const int CLON_SPAWN_RANGE = 700;
	const double MANA_COST = 10;
public:
	ClonSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { costMana_ = MANA_COST; };
	virtual ~ClonSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no est� en cooldown la habilidad y hay mana suficiente
		if (costMana_ <= mana && !skillCD_.isCooldownActive())
		{
			Vector2D dist = Vector2D(HandleEvents::instance()->getRelativeMousePos().getX() - player_->getPos().getX(), HandleEvents::instance()->getRelativeMousePos().getY() - player_->getPos().getY());
			if (dist.magnitude() <= CLON_SPAWN_RANGE)
			{
				player_->removeMana(costMana_);
				player_->createClon();
				skillCD_.initCooldown(COOLDOWN);
				GameManager::instance()->setSkillCooldown(true, Key::R);
			}
		}
	};
};