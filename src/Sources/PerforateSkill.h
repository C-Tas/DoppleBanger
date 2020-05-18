#pragma once
#include "Skill.h"
class PerforateSkill : public Skill
{
private:
	const double COOLDOWN = 2000;	//En milisegundos
	const double MANA_COST = 10;

public:
	PerforateSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) { costMana_ = MANA_COST; };
	~PerforateSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no est� en cooldown la habilidad
		if (mana >= costMana_ && !skillCD_.isCooldownActive())
		{
			player_->removeMana(costMana_);
			player_->setPerforate(true);
			skillCD_.initCooldown(COOLDOWN);
		}
	};
};