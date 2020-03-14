#pragma once
#include "NPC.h"
using namespace std;
class Enemy : public NPC
{
private:
protected:
	int damage_;
	int health_;
public:
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser�n los puestos, si se le pasan valores los editara</summary>
	Enemy(Application* app = nullptr, Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }, SDL_Rect collisionArea = { 0,0,0,0 }, int damage = 0, int health = 0, SDL_Rect frame = { 0,0,0,0 }) :NPC(app, texture, pos, scale, collisionArea), damage_(damage), health_(health) { frame_ = frame; };
	//<summary>Constructor por copia</summary>
	Enemy(Enemy& other) :NPC(other.app_, other.texture_, other.pos_, other.scale_, other.collisionArea_),damage_(other.damage_),health_(other.health_) {};
	//<summary>Constructor por movimiento<summary>
	Enemy(Enemy&& other)noexcept :NPC(other.app_, other.texture_, other.pos_, other.scale_, other.collisionArea_),damage_(other.damage_), health_(other.health_) {};
	//<summary>Destructor</summary>
	virtual ~Enemy() {};
	//<summary>Metodo que llevar� la logica de nuestros enemigos cada enemigo tiene un comportamiento diferente por los que lo unico com�n es el cambio del frame de la animaci�n </summary>
	virtual bool update() {};
	//<summary>Metodo que cambia el frame que se va a renderizar</summary>
	void updateFrame();
	//<summary>Metodo que renderizar� nuestro enemigos, (se ha hecho suponiendo que todos tienen animaci�n </summary>
	virtual void draw() const { texture_->render(destiny_, frame_); };

};

