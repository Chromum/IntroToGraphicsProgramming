#include "GLUTCallbacks.h"
#include "Main.h"
#include "Constants.h"
#include "Sphere.h"
#include "GLObject.h"
#include "ModelLoader.h"


namespace GLUTCallbacks
{
	namespace
	{
		Main* main = nullptr;
	}

	void Init(Main* m)
	{
		main = m;
	}

	void Display()
	{
		if (main != nullptr)
		{
			main->Display();
		}
	}

	void Timer(int preferedRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		main->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferedRefresh - updateTime, GLUTCallbacks::Timer, preferedRefresh - updateTime);
	}


	void KeyboardKeyUp(unsigned char key, int x, int y)
	{
		main->KeyboardUp(key, x, y);
	}

	void KeyboardKeyDown(unsigned char key, int x, int y)
	{
		main->KeyboardDown(key, x, y);
	}

	void OnWindowResize(int width, int height)
	{
		main->screenWidth = width;
		main->screenHeight = height;

		//main->ReBuildProjectionMatrix();
	}

	void MouseClick(int button, int state, int x, int y) 
	{
		Vector3 v3;
		switch (button)
		{
		case GLUT_LEFT_BUTTON:

			InterReturn r = main->sphere->CheckIfIntersect(main->cameraTransform.Position, main->cameraFront);

			if (!r.result)
			{
				ModelLoader ml = ModelLoader();
				std::vector<Mesh*> meshes = ml.LoadMeshAtPath("Models/untitled.obj");



				main->objects.push_back(new GLObject(r.v1, Vector3(.1f, .1f, .1f), 0, meshes, main->displayEvent));
				main->objects.push_back(new GLObject(r.v2, Vector3(.1f, .1f, .1f), 0, meshes, main->displayEvent));


				std::cout << "Hit the sphere" << std::endl;
			}
			else
			{
				std::cout << "Missed the sphere" << std::endl;
			}



			main->leftMouse = !main->leftMouse;
			break;
		//case GLUT_RIGHT_BUTTON:
		//	main->rightMouse = !main->rightMouse;
		//	break;
		//case GLUT_MIDDLE_BUTTON:
		//	main->middleMouse = !main->middleMouse;
		//	break;
		}


	}

	void MouseMove(int x, int y) {
		static bool firstTime = true;
		static Vector2 mouseLastFrame = Vector2(main->screenWidth/2, main->screenHeight/2);
		Vector2 mouseCurrentFrame = Vector2(x, y);

		if (firstTime) {
			mouseLastFrame.x = x;
			mouseLastFrame.y = y;
			firstTime = false;
		}

		float xOffset = mouseCurrentFrame.x - mouseLastFrame.x;
		float yOffset = mouseCurrentFrame.y - mouseLastFrame.y;
		mouseLastFrame = mouseCurrentFrame;

		float sens = 0.1f;

		xOffset *= sens;
		yOffset *= sens;

		static float pitch;
		static float yaw = -90;

		pitch -= yOffset;
		yaw += xOffset;

		main->pitch = pitch;
		main->yaw = yaw;


		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		main->cameraTransform.Rotation.x = (cos(ToRad(yaw)) * cos(ToRad(pitch)));
		main->cameraTransform.Rotation.y = sin(ToRad(pitch));
		main->cameraTransform.Rotation.z = (sin(ToRad(yaw)) * cos(ToRad(pitch)));
		main->cameraFront = main->cameraTransform.Rotation.Normilized();


		if (mouseCurrentFrame.x < 100 || x > GLUT_SCREEN_WIDTH - 100)
		{
			mouseLastFrame.x = GLUT_SCREEN_WIDTH / 2;
			mouseLastFrame.y = GLUT_SCREEN_HEIGHT / 2;
			glutWarpPointer(GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2);
		}
		else if (y < 100 || y > GLUT_SCREEN_HEIGHT - 100)
		{
			mouseLastFrame.x = GLUT_SCREEN_WIDTH / 2;
			mouseLastFrame.y = GLUT_SCREEN_HEIGHT / 2;
			glutWarpPointer(GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2);
		}
		
	}


}

