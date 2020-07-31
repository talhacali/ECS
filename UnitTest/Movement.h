#pragma once
#include "System.h"

class Movement : public ECS::System<Movement>
{
public:
	int velocity_x, velocity_y,velocity_z;
	Movement(int _velocity_x,int _velocity_y,int _velocity_z) : velocity_x(_velocity_x),velocity_y(_velocity_y),velocity_z(_velocity_z){}

	void Init()
	{
		std::cout << "Movement init" << std::endl;
	}

	void Update(float dt)
	{
		std::cout << "Movement update" << std::endl;
	}
};