#include "Sphere.h"
//#include <gl/GL.h>
#include "GLObject.h"
#include "Camera.h"
#include "SceneManager.h"
#include <utility>


void Sphere::Draw() 
{
	glTranslatef(this->Transform.Position.x, this->Transform.Position.y, this->Transform.Position.z);
	glColor3f(0,0,0);
	if(!this->isSelected)
		glutWireSphere(this->Radius,16,16);
	else
		glutSolidSphere(this->Radius, 16, 16);
}

InterReturn Sphere::CheckIfIntersect(Vector3 rayStart, Vector3 rayDirection)
{
	InterReturn r = InterReturn();

	Vector3 origin = rayStart - this->parent->Transform.Position;
	

	float a = rayDirection.SqrMagnitude();
	float b = 2 * ((origin.x * rayDirection.x) + (origin.y * rayDirection.y) + (origin.z * rayDirection.z));
	float c = (((origin.x * origin.x) + (origin.y * origin.y) + (origin.z * origin.z)) - (this->Radius * this->Radius));


	if ((b * b) - (4 * a * c) >= 0)
		r.result = true;
	else
		r.result = false;

	return r;
}
