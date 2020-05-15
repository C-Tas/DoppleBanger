#pragma once
#include "Skill.h"
class RicochetSkill : public Skill
{
private:
	const double COOLDOWN = 5000;	//En milisegundos
	const double MANA_COST = 10;

public:
	RicochetSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Distance) { costMana_ = MANA_COST; };
	~RicochetSkill() {}

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
 		if (!skillCD_.isCooldownActive())
		{
			cout << "Rebote" << endl;
			player_->removeMana(costMana_);
			player_->setRicochet(true);
			skillCD_.initCooldown(COOLDOWN);
		}
	};
};

