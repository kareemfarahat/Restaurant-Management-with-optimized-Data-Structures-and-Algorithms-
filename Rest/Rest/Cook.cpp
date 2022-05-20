#include <iostream>
#include "Cook.h"


Cook::Cook(int id,int s,int b)
{
	ID = id;
	speed = s;
	BreakLimit = b;
	
}

Cook::Cook()
{
	
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}

int Cook::GetFinishTime()
{
	return TimeToFinish;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::setTimeToFinish(Order* O,int ctime)
{
	if (Injured) {
		TimeToFinish = (O->getNumberOfDishes() / (speed * 2)) + ctime  ;
	}
	 
	else {
		TimeToFinish = (O->getNumberOfDishes() / speed) + ctime;
		OrdersMade++;
	}
}

void Cook::setSpeed(int x)
{
	speed = x;
}

void Cook::setBreakDuration(int x)
{ 
	BreakDuration = x;
}

void Cook::setBreakLimit(int x ) 
{
	BreakLimit = x;
}

/*void Cook::setInjured()
{
	Injured = true;
}*/

bool Cook::IsAvailable(int ctime)
{
	
if ( TimeToFinish > ctime ) {
	return false;
}
else if (BreakLimit == OrdersMade) {
	BreakTime(ctime);
	return false;
}

else
	return true;
}



void Cook::BreakTime(int ctime)
{
	
	TimeToFinish = ctime + BreakDuration;
	OrdersMade = 0;
}




