#pragma once

#pragma once

#include "Component.h"

class Transform : public ECS::Component<Transform>
{
public:
	float x, y, z;

	Transform(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};