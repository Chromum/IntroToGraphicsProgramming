
#include "Plane.h"
#include "SceneManager.h"


void Plane::Update()
{
    if (!moving)
        return;

    if ((this->Transform.Position - currentWaypoint).Magnitude() > 10)
    {
        this->Transform.Position = Vector3::MoveTowards(this->Transform.Position, currentWaypoint, speed, SceneManager::instance->deltaTime);

        this->Transform.Rotation.x += 1;
        this->Transform.Rotation.y += 1;
        this->Transform.Rotation.z += 1;
        
    }
    else
    {

        if (currentWaypointIndex >= planeWaypoints.size() - 1)
            currentWaypointIndex = 0;
        else
        {
            currentWaypointIndex++;
        }

        currentWaypoint = planeWaypoints[currentWaypointIndex];
    }
}
