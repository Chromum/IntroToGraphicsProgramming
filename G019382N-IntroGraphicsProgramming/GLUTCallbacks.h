#pragma once
class Main;

namespace GLUTCallbacks
{
	void Init(Main* main);
	void Display();
	void Timer(int preferedRefresh);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardKeyUp(unsigned char key, int x, int y);
	void KeyboardKeyDown(unsigned char key, int x, int y);
};

