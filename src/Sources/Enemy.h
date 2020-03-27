#pragma once
#include "Actor.h"

using namespace std;
class Enemy : public Actor
{
protected:
	//<summary>Metodo para hacer daño hay que editarlo</summary>
	void doDamage() {};
	//<summary>Metodo que mata a este enemigo</summary>
	void die();

public:
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser�n los puestos, si se le pasan valores los editara</summary>
	Enemy(Application* app = nullptr, vector<Texture*> textures = { nullptr }, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }, SDL_Rect collisionArea = { 0,0,0,0 }, Stats stats = {}, SDL_Rect frame = { 0,0,0,0 }, vector<int> numberFrames = { 0 }) :Actor(app, textures, pos, scale, collisionArea, frame, numberFrames) { currStats_ = stats; };
	//<summary>Constructor por copia</summary>
	Enemy(Enemy& other) :Actor(other.app_, other.textures_, other.pos_, other.scale_, other.collisionArea_) { currStats_ = other.currStats_; };
	//<summary>Constructor por movimiento<summary>
	Enemy(Enemy&& other)noexcept :Actor(other.app_, other.textures_, other.pos_, other.scale_, other.collisionArea_) { currStats_ = other.currStats_; };
	//<summary>Destructor</summary>
	virtual ~Enemy() {};
	//<summary>Metodo que llevar� la logica de nuestros enemigos cada enemigo tiene un comportamiento diferente por los que lo unico com�n es el cambio del frame de la animaci�n </summary>
	virtual bool update() { updateFrame(); return false; };
	virtual void onCollider() { /*Colisi�n con jugador*/ };
	//<summary>Metodo que renderizar� nuestro enemigos, (se ha hecho suponiendo que todos tienen animaci�n </summary>
	virtual void draw() const { texture_->render(destiny_, frame_); };

	//<summary>Metodo que resta vida al enemigo. Si es cero o menor, lo mata</summary>
	void takeDamage(int dmg) {
		currStats_.health_ -= dmg;
		if (currStats_.health_ <= 0) die();
	};
};

