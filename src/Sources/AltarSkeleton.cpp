#include "AltarSkeleton.h"

void AltarSkeleton::removeThisSkeleton()
{
	altarOwner_->elimina();
}

void AltarSkeleton::initDie()
{
	Skeleton::initDie();
	removeThisSkeleton();
}

