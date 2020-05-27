#pragma once
#include "Skill.h"
class RicochetSkill : public Skill
{
private:
	const double COOLDOWN = 10000;	//En milisegundos
	const double MANA_COST = 0.10;	//Porcentaje de mana

public:
	RicochetSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) {};
	~RicochetSkill() {}

	virtual void action() {
		double mana = player_->getMaxMana();
		costMana_ = mana * MANA_COST;
		//Si no est� en cooldown la habilidad
 		if (costMana_ <= player_->getMana() && !skillCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->activeRicochet();
			skillCD_.initCooldown(COOLDOWN);
		}
	};
};

