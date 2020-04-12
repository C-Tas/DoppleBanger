#pragma once
#include "Enemy.h"
class Pumpkin :
	public Enemy
{
private:
	///<summary>vector con todos los objetivos del cangrejo</summary>
	vector<Point2D> targetsVector_;
	///<summary>booleano que determina si debe o no seguir al jugador</summary>
	bool followPlayer_=false;
	///<summary>Int que determina el radio al que empieza a disparar</summary>
	int radioMayor;
	///<summary>Int que determina el radio al que empieza a correr hacia el player</summary>
	int radioMenor;
	///<summary>devuelve si ataca o no</summary>
	bool attack();
	///<summary>Devuelve si hay un enemigo en rango y establece cual es el más cercano </summary>
	bool isATargetInRange();
public:
	virtual bool update();
	////<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	//Pumpkin(Application* app = nullptr, vector<Texture*> textures = { nullptr }, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }, SDL_Rect collisionArea = { 0,0,0,0 }, Stats stats = {}, SDL_Rect frame = { 0,0,0,0 }, vector<int> numberFrames = { 0 }, vector<Point2D>targets = {}) :Enemy(app, textures, pos, scale, collisionArea, stats, frame, numberFrames), targetsVector_(targets) { currStats_ = stats; };
	////<summary>Constructor por copia</summary>
	//Pumpkin(Pumpkin& other) :Enemy(other.app_, other.textures_, other.pos_, other.scale_, other.collisionArea_) { currStats_ = other.currStats_; };
	////<summary>Constructor por movimiento<summary>
	//Pumpkin(Pumpkin&& other)noexcept :Enemy(other.app_, other.textures_, other.pos_, other.scale_, other.collisionArea_) { currStats_ = other.currStats_; };

	~Pumpkin() {};
};

