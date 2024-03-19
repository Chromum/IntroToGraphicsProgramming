#pragma once
class Main;

namespace GLUTCallbacks
{
	void Init(Main* main);
	void Display();
	void Timer(int preferedRefresh);
};

