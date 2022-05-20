#pragma once
#include "Event.h"
class CancelEvent : public Event
{
	
public:
	CancelEvent(int eTime, int oID);
	//Add more constructors if needed

	virtual void Execute(Restaurant* pRest);	//override execute function

};