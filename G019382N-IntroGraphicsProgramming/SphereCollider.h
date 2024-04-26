#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(double Radius, int slices, int stacks);
	bool CheckIfColliding(Collider secondCollider) override;
	
};

