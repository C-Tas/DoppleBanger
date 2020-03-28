#include "ShipObject.h"
#include "HandleEvents.h"
#include "StashState.h"
#include "SaveLoadState.h"
#include "SelectLevelState.h"

void ShipObject::onColliderStash()
{
	app_->getGameStateMachine()->pushState(new StashState(app_));
}

void ShipObject::onColliderDoor()
{
	app_->getGameStateMachine()->pushState(new SaveLoadState(app_, false));
}

void ShipObject::onColliderWheel(int island)
{
	app_->getGameStateMachine()->pushState(new SelectLevelState(app_, island));
}

