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
	const double MANA_COST = 10;

public:
	WhirlwindSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { cooldown_ = COOLDOWN;  costMana_ = MANA_COST; };
	virtual ~WhirlwindSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no est� en cooldown la habilidad
		if (mana >= costMana_ && ((SDL_GetTicks() - lastTimeUsed_) / 1000 > cooldown_ || lastTimeUsed_ == 0))
		{
			player_->removeMana(costMana_);
			//Consigue la lista de los enemigos golpeados y les hace da�o
			Vector2D playerCenter = Vector2D(player_->getPosX() + player_->getScaleX(), player_->getPosY() + player_->getScaleY());
			list<Enemy*> enemies = CollisionCtrl::instance()->getEnemiesInArea(playerCenter, RADIUS);
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				(*it)->receiveDamage(player_->getMeleeDmg() * BONUS);

			lastTimeUsed_ = SDL_GetTicks();
		}
	};
};