#include "Equipment.h"
#include <iostream> //Include temporal

void Equipment::writeStats()
{
	switch (type_)
	{
	case Armor:
		std::cout << "Armor\n";
		break;
	case Boots:
		std::cout << "Boots\n";
		break;
	case Gloves:
		std::cout << "Gloves\n";
		break;
	case Sword:
		std::cout << "Sword\n";
		break;
	case Gun:
		std::cout << "Gun\n";
		break;
	}

	std::cout << modifiers_.meleeDmg_ << "\n";
	std::cout << modifiers_.distDmg_ << "\n";
	std::cout << modifiers_.health_ << "\n";
	std::cout << modifiers_.armor_ << "\n";
	std::cout << modifiers_.moveSpeed_ << "\n";
	std::cout << modifiers_.crit_ << "\n";
	std::cout << modifiers_.meleeRate_ << "\n";
	std::cout << modifiers_.distRate_ << "\n";
}