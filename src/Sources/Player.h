#pragma once
#include "Actor.h"
class Player : public Actor
{
public:
	Player(Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }) : Actor(texture, pos, scale) {};
	~Player() {};
	void update() {};
};