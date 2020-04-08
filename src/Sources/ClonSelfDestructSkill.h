#pragma once

#include "Skill.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

class ClonSelfDestructSkill : public Skill
{
private:
	const int RADIUS = 150;
	const int BONUS = 1.5;
	const int COOLDOWN = 5;

public:
	ClonSelfDestructSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; };
	virtual ~ClonSelfDestructSkill() {};

	virtual void action() {
		//Si no está en cooldown la habilidad
		if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			cout << "\nExplosión\n";
			//Consigue la lista de los enemigos golpeados y les hace daño
			Vector2D clonCenter = Vector2D(player_->getClonPos().getX() + player_->getClonScale().getX(), player_->getClonPos().getY() + player_->getClonScale().getY());
			list<Enemy*> enemies = CollisionCtrl::instance()->getEnemiesInArea(clonCenter, RADIUS);
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				(*it)->takeDamage(player_->getAd() * BONUS);

			player_->killClon();
			lastTimeUsed_ = SDL_GetTicks();
		}
	};
};

