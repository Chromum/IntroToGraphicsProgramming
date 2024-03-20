#pragma once
#include <iostream>
#include <functional>
#include <vector>

class EventHandler
{
public:
	std::string name;
	EventHandler(std::string name);
	void AddHandler(std::function<void()> handler);
	void FireEvent();
private:
	std::vector < std::function<void()>> handlers;
};

