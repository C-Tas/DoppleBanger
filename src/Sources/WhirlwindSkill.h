#pragma once

#include "Skill.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

class WhirlwindSkill : public Skill
{
private:
	const int RADIUS = 150;
	const int BONUS = 1.3;
	const int COOLDOWN = 5;

public:
	WhirlwindSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN; };
	virtual ~WhirlwindSkill() {};

	virtual void action() {
		//Si no está en cooldown la habilidad
		if ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0)
		{
			cout << "\nGolpe\n";
			//Consigue la lista de los enemigos golpeados y les hace daño
			Vector2D playerCenter = Vector2D(player_->getPosX() + player_->getScaleX(), player_->getPosY() + player_->getScaleY());
			list<Enemy*> enemies = CollisionCtrl::instance()->getEnemiesInArea(playerCenter, RADIUS);
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				(*it)->takeDamage(player_->getAd() * BONUS);

			lastTimeUsed_ = SDL_GetTicks();
		}
	};
};