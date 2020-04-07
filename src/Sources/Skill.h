#pragma once
#include "GameManager.h"

enum class SkillBranch { Physical, Distance, Ghost };

class Skill
{

protected:
	SkillType type_;
	SkillBranch branch_;
	double lastTimeUsed_ = 0;
	double cooldown_ = 0;

public:
	///<summary>Constructora</summary>
	Skill(SkillType type, SkillBranch branch) : type_(type),  branch_(branch) {};

	///<summary>Destructora</summary>
	virtual ~Skill() {};
	///<summary>Método a redefinir en las clases hijas. Define que hace la skill (si es activa) 
	///o los atributos que aumenta (si es pasiva) </summary>
	//virtual void action() = 0;

	//Temporal para comprobar que funciona
	virtual void action() { cout << "Skill que hace cosas" << endl; }

#pragma region getters
	///<summary>Devuelve si la skill es una pasiva o una activa</summary>
	//SkillType getSkillType() { return type_; };
	///<summary>Devuelve a que rama de habilidad pertenece esta skill</summary>
	SkillBranch getSkillBranch() { return branch_; };
#pragma endregion
	
};

