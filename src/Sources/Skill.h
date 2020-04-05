#pragma once

enum SkillType { Active, Pasive };
enum SkillBranch { Physical, Distance, Ghost };

class Skill {
private:
	SkillType type_;
	SkillBranch branch_;

protected:
	//Tiempo de cooldown de la habilidad (inicializarla en cada hija)
	double cooldown_ = 0;
	//Determina si el cooldown est� actualmente activo o no
	bool cooldownActive_ = false;

public:
	///<summary>Constructora</summary>
	Skill(SkillType type, SkillBranch branch) : type_(type), branch_(branch) {};

	///<summary>Destructora</summary>
	virtual ~Skill() {};
	///<summary>M�todo a redefinir en las clases hijas. Define que hace la skill (si es activa) 
	///o los atributos que aumenta (si es pasiva) </summary>
	virtual void action() = 0;

#pragma region getters
	///<summary>Devuelve si la skill es una pasiva o una activa</summary>
	SkillType getSkillType() { return type_; };
	///<summary>Devuelve a que rama de habilidad pertenece esta skill</summary>
	SkillBranch getSkillBranch() { return branch_; };
	///<summary>Devuelve si el cooldown est� activado o no</summary>
	bool getCooldownActive() { return cooldownActive_; };
#pragma endregion
	
};

