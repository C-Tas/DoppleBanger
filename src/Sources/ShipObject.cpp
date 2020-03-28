#include "ShipObject.h"
#include "HandleEvents.h"
#include "StashState.h"
#include "SaveLoadState.h"
#include "SelectLevelState.h"
#include "GameManager.h"

void ShipObject::onCollider()
{
	cb_(app_); //Llama al callback
}

void ShipObject::initObject()
{

}
