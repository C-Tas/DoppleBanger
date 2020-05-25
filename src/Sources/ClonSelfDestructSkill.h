#pragma once

#include "Skill.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

class ClonSelfDestructSkill : public Skill
{
private:
	const int RADIUS = 150;
	const int BONUS = 2;
	const double COOLDOWN = 5000;	//En milisegundos
	Cooldown destructCD_;			//Cooldown
	const int MANA_COST = 10;

public:
	ClonSelfDestructSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { costMana_ = MANA_COST; };
	virtual ~ClonSelfDestructSkill() {};

	virtual void action() {
		double mana = player_->getMana();
		//Si no está en cooldown la habilidad
		if (mana >= costMana_ && player_->getClon() != nullptr && !destructCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->getClon()->initSelfDestruction();
			//Consigue la lista de los enemigos golpeados y les hace daño
			Vector2D clonCenter = Vector2D(player_->getClon()->getPos().getX() + player_->getClon()->getScale().getX(), player_->getClon()->getPos().getY() + player_->getClon()->getScale().getY());
			list<Enemy*> enemies = CollisionCtrl::instance()->getEnemiesInArea(clonCenter, RADIUS);
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				(*it)->receiveDamage((int)round(player_->getMeleeDmg() * BONUS));

			if (player_->getClon() != nullptr) destructCD_.initCooldown(COOLDOWN);
		}
	};
	virtual void update() {
		if (destructCD_.isCooldownActive()) {
			destructCD_.updateCooldown();
		}
	}
};