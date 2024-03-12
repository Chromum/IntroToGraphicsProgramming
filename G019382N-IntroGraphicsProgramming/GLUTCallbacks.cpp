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
}
