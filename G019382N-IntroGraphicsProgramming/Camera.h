#pragma once
#include "SceneObject.h"
#include "GL/freeglut.h"
#include "GL/glut.h"
#include <gl/GL.h>



class Camera : public SceneObject {
public:
	static Camera* instance;

	bool isClickDown = false;
	SceneObject* targetObjectToFollow;
	Vector3 cameraForward;
	float pitch, yaw;

	Vector3 lookat_point;

	Camera(std::string name) : SceneObject(name) {
		if (instance == nullptr)
		{
			instance = this;
			this->Transform.Position = Vector3(28.4586182, 15.2535725, 46.5471077);
		}
		else
			delete(this);
	}

	void Update() {

		if (targetObjectToFollow != nullptr)
			FollowObject();
		else if (!isClickDown)
			CameraFollowMouse();


		ReBuildProjectionMatrix();
	} 

	void CameraFollowMouse()
	{
		this->lookat_point = this->cameraForward + this->Transform.Position;
	}

	void FollowObject() {
		this->lookat_point = this->targetObjectToFollow->Transform.Position;
	}

	void ReBuildProjectionMatrix()
	{
		Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);

		glMatrixMode(GL_MODELVIEW);
		{
			glLoadIdentity();
			gluLookAt(
				this->Transform.Position.x,
				this->Transform.Position.y,
				this->Transform.Position.z,

				this->lookat_point.x,
				this->lookat_point.y,
				this->lookat_point.z,

				cameraUp.x,
				cameraUp.y,
				cameraUp.z);
		}

		glutPostRedisplay();
	}



};