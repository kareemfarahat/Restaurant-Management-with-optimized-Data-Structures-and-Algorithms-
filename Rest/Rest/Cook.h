#pragma once

#include "..\Defs.h"
#include"Order.h"

#pragma once
class Cook
{
	int ID ;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int BreakLimit; // Number of orders that the cook can make before having a break 
	bool Injured = false ; // if the the cook is injured this should be true
	int OrdersMade=0; // Number of orders the cook had made and it is seted to zero after every break
	int TimeToFinish=0; // The time the current order will be finished
	int BreakDuration;

public:
	Cook(int,int,int ); // constructer that get arguments (ID / Speed / Break Time) in order
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	int GetFinishTime();
	void setID(int);
	void setType(ORD_TYPE) ;
	void setTimeToFinish( Order* ,int);
	void setSpeed(int);
	void setBreakDuration(int);
	void setBreakLimit(int);
	//void setInjured();
	bool IsAvailable(int);
	void BreakTime(int);
};
