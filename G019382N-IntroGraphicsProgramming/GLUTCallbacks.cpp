#include "GLUTCallbacks.h"
#include "Main.h"
#include "Constants.h"
#include "Sphere.h"
#include "GLObject.h"
#include "ModelLoader.h"
#include "Camera.h"


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
		glutTimerFunc(8 - updateTime, GLUTCallbacks::Timer, preferedRefresh - 8);
		
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

			if (state == GLUT_UP)
			{
				main->leftMouse = false;
			}
				
			else
			{
				main->leftMouse = true;
				main->SelectObject();
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_UP)
			{
				main->rightMouse = false;
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			}

			else
			{
				main->rightMouse = true;
				glutWarpPointer(GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2);
				glutSetCursor(GLUT_CURSOR_NONE);
			}
			break;
		}


	}

	void MouseMove(int x, int y) {
		static bool firstTime = true;
		static Vector2 mouseLastFrame = Vector2(main->screenWidth / 2, main->screenHeight / 2);
		Vector2 mouseCurrentFrame = Vector2(x, y);

		if (firstTime) {
			mouseLastFrame.x = x;
			mouseLastFrame.y = y;
			firstTime = false;
		}

		if (main->rightMouse)
		{
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


			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			Camera::instance->pitch = pitch;
			Camera::instance->yaw = yaw;

			Camera::instance->Transform.Rotation = Vector3((cos(ToRad(yaw)) * cos(ToRad(pitch))),
				sin(ToRad(pitch)), (sin(ToRad(yaw)) * cos(ToRad(pitch))));
			Camera::instance->cameraForward = Camera::instance->Transform.Rotation.Normilized();



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


}

