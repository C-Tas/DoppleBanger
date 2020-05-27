#pragma once
#include "Skill.h"
class PerforateSkill : public Skill
{
private:
	const double COOLDOWN = 4000;	//En milisegundos
	const double MANA_COST = 0.05;	//Porcentaje de mana

public:
	PerforateSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) { costMana_ = MANA_COST; };
	~PerforateSkill() {};

	virtual void action() {
		double mana = player_->getMaxMana();
		costMana_ = mana * MANA_COST;
		//Si no est� en cooldown la habilidad
		if (costMana_ <= player_->getMana() && !skillCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->setPerforate(true);
			skillCD_.initCooldown(COOLDOWN);
		}
	};
};