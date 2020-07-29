#pragma once
#include "Entity.h"
#include <string>

class Player : public ECS::Entity<Player>
{
public:
	std::string name;
	int id;
	Player(std::string _name, int _id) : id(_id), name(_name) {}
};