#include "EventArray.h"

Event::Event(float time, Body* body1, Body* body2, bool wall) : time(time), body1(body1), body2(body2), wall(wall)
{}

EventArray::EventArray()
{}

void EventArray::addEvent(Event* e)
{
	array.push_back(e);
}

void EventArray::deleteEvent(Event* e)
{
	if (e == nullptr)
		return;
	int eventPos = 0;
	for (eventPos; eventPos < array.size(); eventPos++)
		if (array[eventPos] == e)
			break;
	m_lastDeletedEvent = array[eventPos];
	array.erase(std::begin(array) + eventPos);
}

void EventArray::deleteBodyEvent(Body* b)
{
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i]->body1 == b || array[i]->body2 == b)
		{
			m_lastDeletedEvent = array[i];
			array.erase(std::begin(array) + i);
			i--;	
		}
	}
}

void EventArray::findNextEvent()
{
	float time = INFINITY;

	for (auto const& event : array)
	{
		if (event->time < time)
		{
			time = event->time;
			m_nextEvent = event;
		}
	}
}

Event* EventArray::getNextEvent()
{
	return m_nextEvent;
}

Event* EventArray::nextEvent()
{
	findNextEvent();

	return getNextEvent();
}

Event* EventArray::getLastDeletedEvent()
{
	return m_lastDeletedEvent;
}
