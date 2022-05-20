#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	//int Distance;	//The distance (in meters) between the order location and the resturant 
	int NumberOfDishes;
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime, waitingTime;	//arrival, service start, and finish times
	double priority;
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(ORD_TYPE r_Type, int AT, int id, int size, double mony);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	int getNumberOfDishes();
	int getArrtime();
	int getFinishTime();
	int getServTime();
	int getWaitTime();
	void setFinishTime(int);
	void setServTime(int);
	void setWaitTime(int);
	double getmoney();
	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	double getPriority();
	int getSize();
	void setPriority();
	//void SetDistance(int d);
	//int GetDistance() const;
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif