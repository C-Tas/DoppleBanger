#pragma once

#include "Skill.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

class WhirlwindSkill : public Skill
{
private:
	const double COOLDOWN = 5000;	//En milisegundos
	const double MANA_COST = 0.15;	//Porcentaje de mana

public:
	WhirlwindSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) {};
	virtual ~WhirlwindSkill() {};

	virtual void action() {
		double mana = player_->getMaxMana();
		costMana_ = mana * MANA_COST;
		//Si no est� en cooldown la habilidad
		if (costMana_ <= player_->getMana() && !skillCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->initWhirl();

			skillCD_.initCooldown(COOLDOWN);
		}
	};
};