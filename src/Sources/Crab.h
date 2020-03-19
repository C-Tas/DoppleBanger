#pragma once
#include "Enemy.h"
#include <vector>
class Crab :
	public Enemy
{
private:
	vector<Point2D> targetVector_;
	int actualTarget_;
	int totalTargets_;
	void updateTarget() { actualTarget_ = (actualTarget_ + 1) % totalTargets_; };
public:
	Crab(Application* app = nullptr, Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }, SDL_Rect collisionArea = { 0,0,0,0 }, Stats stats = {}, SDL_Rect frame = { 0,0,0,0 }, int numberFrames = 0, vector<Point2D>targets = {}, int totalTargets = 0) :Enemy(app,texture,pos,scale,collisionArea,stats,frame,numberFrames),targetVector_(targets),totalTargets_(totalTargets) { actualTarget_ = 0; };
	virtual ~Crab() {};
	virtual bool update();
};

