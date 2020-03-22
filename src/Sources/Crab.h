#pragma once
#include "Enemy.h"
#include <vector>
class Crab :
	public Enemy
{
private:
	vector<Point2D> targetsVector_;
	int actualTarget_;
	void updateTarget() { actualTarget_ = (actualTarget_ + 1) % targetsVector_.size(); }
public:
	virtual bool update();
	//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser?n los puestos, si se le pasan valores los editara</summary>
	Crab(Application* app = nullptr, Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }, SDL_Rect collisionArea = { 0,0,0,0 }, Stats stats = {}, SDL_Rect frame = { 0,0,0,0 }, int numberFrames = 0, vector<Point2D>targets = {}) :Enemy(app, texture, pos, scale, collisionArea, stats, frame, numberFrames), targetsVector_(targets), actualTarget_(0) { currStats_ = stats; };
	//<summary>Constructor por copia</summary>
	Crab(Crab& other) :Enemy(other.app_, other.texture_, other.pos_, other.scale_, other.collisionArea_) { currStats_ = other.currStats_; };
	//<summary>Constructor por movimiento<summary>
	Crab(Crab&& other)noexcept :Enemy(other.app_, other.texture_, other.pos_, other.scale_, other.collisionArea_) { currStats_ = other.currStats_; };
};


