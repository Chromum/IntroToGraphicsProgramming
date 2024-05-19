#include "GLObject.h"

class Plane : public GLObject
{
public:
	Plane(std::string name, Vector3 pos,Vector3 rot, Vector3 scale, std::vector<Mesh*> meshes, EventHandler* displayEvent, float selectSphereRadius) :
		GLObject(name, pos,rot, scale, meshes, displayEvent, selectSphereRadius)
	{
		planeWaypoints.push_back(Vector3(100.6, 80.0, -102.2));
		planeWaypoints.push_back(Vector3(100.6, 80.0, -82.2));

		planeWaypoints.push_back(Vector3(100.6, 80.0, 84.4));
		planeWaypoints.push_back(Vector3(100.6, 80.0, 104.4));

		planeWaypoints.push_back(Vector3(80.6, 80.0, 104.4));
		planeWaypoints.push_back(Vector3(-86.0, 80.0, 104.4));

		planeWaypoints.push_back(Vector3(-106.0, 80.0, 104.4));
		planeWaypoints.push_back(Vector3(-106.0, 80.0, 84.4));

		planeWaypoints.push_back(Vector3(-105.8, 80.0, -82.2));
		planeWaypoints.push_back(Vector3(-105.8, 80.0, -102.2));

		planeWaypoints.push_back(Vector3(-85.8, 80.0, -102.2));
		planeWaypoints.push_back(Vector3(80.6, 80.0, -102.2));


		currentWaypoint = planeWaypoints[0];
	}

	std::vector<Vector3> planeWaypoints;
	Vector3 currentWaypoint;
	int currentWaypointIndex = 0;
	float speed = 1;
	float turnSpeed;
	bool moving = true;
	void Update() override;

};
