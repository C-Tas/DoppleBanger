#pragma once

#include "Skill.h"
#include "Enemy.h"
#include "CollisionCtrl.h"

class ClonSelfDestructSkill : public Skill
{
private:
	const double RADIUS = player_->getScaleX()/2;
	const double DAMAGE = 500;
	const double COOLDOWN = 5000;	//En milisegundos
	Cooldown destructCD_;			//Cooldown
	const double MANA_COST = 0.20;		//Porcentaje de mana

public:
	ClonSelfDestructSkill(Player* player) : Skill(player, SkillType::Active, SkillBranch::Physical) { costMana_ = MANA_COST; };
	virtual ~ClonSelfDestructSkill() {};

	virtual void action() {
		double mana = player_->getMaxMana();
		costMana_ = mana * MANA_COST;
		//Si no está en cooldown la habilidad
		if (costMana_ <= player_->getMana() && player_->getClon() != nullptr && !destructCD_.isCooldownActive())
		{
			player_->addMana(-costMana_);
			player_->getClon()->initSelfDestruction();
			//Consigue la lista de los enemigos golpeados y les hace daño
			Vector2D clonCenter = Vector2D(player_->getClon()->getPos().getX() + player_->getClon()->getScale().getX(), player_->getClon()->getPos().getY() + player_->getClon()->getScale().getY());
			list<Enemy*> enemies = CollisionCtrl::instance()->getEnemiesInArea(clonCenter, RADIUS);
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
				(*it)->receiveDamage((int)round(DAMAGE));

			if (player_->getClon() != nullptr) destructCD_.initCooldown(COOLDOWN);
		}
	};
	virtual void update() {
		if (destructCD_.isCooldownActive()) {
			destructCD_.updateCooldown();
		}
	}
};