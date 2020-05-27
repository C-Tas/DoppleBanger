#pragma once
#include "Skeleton.h"
#include "Altar.h"

class AltarSkeleton : public Skeleton
{
public:
	AltarSkeleton(Application* app, Vector2D pos, Vector2D scale, Altar* altar) :Skeleton(app, pos, scale), altarOwner_(altar) { initObject(); };

	virtual ~AltarSkeleton() {};

	Altar* altarOwner_ = nullptr;
	void removeThisSkeleton();
	virtual void initDie();

};

