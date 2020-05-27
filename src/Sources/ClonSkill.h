#pragma once

#include "Skill.h"
#include "CollisionCtrl.h"

class ClonSkill : public Skill
{
private:
	const double COOLDOWN = 10000;	//En milisegundos
	const double CLON_SPAWN_RANGE = player_->getScaleX() * 3.5;
	const double MANA_COST = 0.10;	//Porcentaje de mana
public:
	ClonSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) {};
	virtual ~ClonSkill() {};

	virtual void action() {
		double mana = player_->getMaxMana();
		costMana_ = mana * MANA_COST;
		Vector2D dist = Vector2D(HandleEvents::instance()->getRelativeMousePos().getX() - player_->getPos().getX(), HandleEvents::instance()->getRelativeMousePos().getY() - player_->getPos().getY());
		//Si no est� en cooldown la habilidad y hay mana suficiente
		if (costMana_ <= player_->getMana() && !skillCD_.isCooldownActive() && dist.magnitude() <= CLON_SPAWN_RANGE)
		{
			player_->addMana(-costMana_);
			player_->createClon();
			skillCD_.initCooldown(COOLDOWN);
			GameManager::instance()->setSkillCooldown(true, Key::R);
		}
	};
};