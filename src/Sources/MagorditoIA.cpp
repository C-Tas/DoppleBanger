#include "MagorditoIA.h"

bool MagorditoIA::update()
{
	if (magordito_->isAlive()) {
		return false;
	}
	else
	{
		return true;
	}
}
