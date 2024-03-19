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


	
}
