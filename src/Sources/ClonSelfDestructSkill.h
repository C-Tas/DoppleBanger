#pragma once

#include "Skill.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

class ClonSelfDestructSkill : public Skill
{
private:
	const int RADIUS = 150;
	const int BONUS = 1.5;
	const int COOLDOWN = 2;
	const int MANA_COST = 10;

public:
	ClonSelfDestructSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; costMana_ = MANA_COST; };
	virtual ~ClonSelfDestructSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
		if (player_->getClon() != nullptr && ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0))
		{
			
			cout << "\nExplosión\n";
			player_->removeMana(costMana_);
			//Consigue la lista de los enemigos golpeados y les hace daño
			Vector2D clonCenter = Vector2D(player_->getClon()->getPos().getX() + player_->getClon()->getScale().getX(), player_->getClon()->getPos().getY() + player_->getClon()->getScale().getY());
			list<Enemy*> enemies = CollisionCtrl::instance()->getEnemiesInArea(clonCenter, RADIUS);
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				(*it)->receiveDamage(player_->getMeleeDmg() * BONUS);

			if (player_->killClon()) lastTimeUsed_ = SDL_GetTicks();
		}
	};
};

