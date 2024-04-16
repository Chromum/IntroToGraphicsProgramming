#include "GLUTCallbacks.h"
#include "Main.h"


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

		main->ReBuildProjectionMatrix();
	}

	void MouseClick(int button, int state, int x, int y) 
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			main->leftMouse = !main->leftMouse;
			break;
		case GLUT_RIGHT_BUTTON:
			main->rightMouse = !main->rightMouse;
			break;
		case GLUT_MIDDLE_BUTTON:
			main->middleMouse = !main->middleMouse;
			break;
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
		static float yaw;

		pitch += xOffset;
		yaw += yOffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		main->cameraTransform.Rotation.x = -(cos(ToRad(pitch)) * cos(ToRad(yaw)));
		main->cameraTransform.Rotation.y = -sin(ToRad(yaw));
		main->cameraTransform.Rotation.z = -(sin(ToRad(pitch)) * cos(ToRad(yaw)));
		main->cameraFront = main->cameraTransform.Rotation.Normilized();


	}


}

