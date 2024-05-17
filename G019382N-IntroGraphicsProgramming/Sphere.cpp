#include "Sphere.h"
//#include <gl/GL.h>
#include "GLObject.h"
#include "Camera.h"

void Sphere::Draw(Vector3 col) 
{
	glPushMatrix();
	Vector3 e = (Camera::instance->cameraForward + Camera::instance->Transform.Position);
	glTranslatef(e.x, e.y, e.z);
	glColor3f(col.x, col.y, col.z);
	glutWireSphere(this->Radius,16,16);
	glPopMatrix();
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
