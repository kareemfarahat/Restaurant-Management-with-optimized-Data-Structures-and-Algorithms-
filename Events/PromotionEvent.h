#pragma once
#include "Event.h"
class PromotionEvent : public Event
{
private:
	double ExMoney;
public:
	PromotionEvent(int eTime, int oID,double );
	//Add more constructors if needed

	virtual void Execute(Restaurant* pRest);	//override execute function

};