#pragma once

#include "main.hpp"

class Body;

class Event
{
public:
	Event(float time, Body* body1, Body* body2, bool wall);

	float time;
	int i1;
	Body* body1;
	int i2;
	Body* body2;
	bool wall;
};

class EventArray
{
public:
	EventArray();
	~EventArray();

	void addEvent(Event* e);
	void deleteEvent(Event* e);
	void deleteBodyEvent(Body* b);

	void findNextEvent();
	Event* getNextEvent();
	Event* nextEvent();

	Event* getLastDeletedEvent();

private:
	std::vector<Event*> array{};
	Event* m_lastDeletedEvent = nullptr;
	Event* m_nextEvent = nullptr;
};

