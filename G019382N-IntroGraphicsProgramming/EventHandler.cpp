#include "EventHandler.h"

EventHandler::EventHandler(std::string name)
{
	this->name = name;
}

void EventHandler::AddHandler(std::function<void()> handler)
{
	handlers.push_back(handler);
}

void EventHandler::FireEvent()
{
	for (auto& handler : handlers)
	{
		handler();
	}
}
