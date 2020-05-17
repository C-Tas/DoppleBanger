#include "ShipObject.h"

void ShipObject::onCollider()
{
	if (cb_ != nullptr) {
		cb_(app_); //Llama al callback
	}
}