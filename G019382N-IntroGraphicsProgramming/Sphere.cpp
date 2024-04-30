#include "Sphere.h"

void Sphere::Draw() //https://antongerdelan.net/opengl/raycasting.html
{
	this->Radius = (this->Transform.Scale.Magnitude());

	glPushMatrix();
	glTranslatef(this->Transform.Position.x, this->Transform.Position.y, this->Transform.Position.z);
	glutWireSphere(this->Radius,16,16);
	glPopMatrix();

}

InterReturn Sphere::CheckIfIntersect(Vector3 rayStart, Vector3 rayDirection)
{
	InterReturn r = InterReturn();

	Vector3 L = this->Transform.Position - rayStart;
	float tC = L.Dot(rayDirection);
	if (tC < 0) {
		r.result = false;
		return r;
	}


	float D = std::sqrt((tC * tC) - (L * L).Magnitude());

	if (D > this->Radius) {
		r.result = false;
		return r;
	};

	float tc1 = std::sqrt((this->Radius * this->Radius) - (D * D));

	float t1 = tC - tc1;
	float t2 = tC + tc1;

	Vector3 interPoint1 = rayStart + rayDirection * t1;
	Vector3 interPoint2 = rayStart + rayDirection * t2;

	r.v1 = interPoint1;
	r.v2 = interPoint2;

	r.result = true;
	return r;
}
