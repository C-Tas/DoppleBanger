#pragma once

#include "Skill.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

class WhirlwindSkill : public Skill
{
private:
	const int RADIUS = 150;
	const int BONUS = 1;
	const double COOLDOWN = 5000;	//En milisegundos
	const double MANA_COST = 10;

public:
	WhirlwindSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { costMana_ = MANA_COST; };
	virtual ~WhirlwindSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no est� en cooldown la habilidad
		if (mana >= costMana_ && !skillCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->initWhirl();

			skillCD_.initCooldown(COOLDOWN);
		}
	};
};