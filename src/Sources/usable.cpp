#include "usable.h"
#include "Player.h"

void usable::use(Player* player)
{
	player->usePotion(value_, type_);
	used_ = true;
}


