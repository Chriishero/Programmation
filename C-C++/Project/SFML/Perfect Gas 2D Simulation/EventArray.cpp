#include "EventArray.h"

Event::Event(float time, Body* body1, Body* body2, bool wall) : time(time), body1(body1), body2(body2), wall(wall)
{}

EventArray::EventArray()
{}

EventArray::~EventArray()
{
	for (int i = 0; i < array.size(); i++)
		delete array[i];
}

void EventArray::addEvent(Event* e)
{
	array.push_back(e);
}

void EventArray::deleteEvent(Event* e)
{
	int eventPos = 0;
	if (e == nullptr)
		return;
	for (eventPos; eventPos < array.size(); eventPos++)
		if (array[eventPos] == e)
			break;
	if (eventPos == array.size())
		return;
	m_lastDeletedEvent = array[eventPos];
	array.erase(std::begin(array) + eventPos);
}

void EventArray::deleteBodyEvent(Body* b)
{
	if (b == nullptr)
		return;
	for (int i = 0; i < array.size(); i++)
	{
		if ((array[i]->body1 == b || array[i]->body2 == b))
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
		//printf("potential next event time %f : ", event->time);
		if (event->time <= 0.0f || event->body1 == nullptr)
			continue;
		else if (event->time < time && event->time > 0.0f)
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
	while (m_nextEvent->time <= 0.0f)
	{
		deleteEvent(m_nextEvent);
		findNextEvent();
	}
	return m_nextEvent;
}

Event* EventArray::getLastDeletedEvent()
{
	return m_lastDeletedEvent;
}
