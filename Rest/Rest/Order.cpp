#include "Order.h"

Order::Order(ORD_TYPE r_Type, int AT, int id, int size,double mony)
{
	ID = id;
	type = r_Type;
	ArrTime = AT;
	NumberOfDishes = size;
	totalMoney = mony;
	status = WAIT;
	priority = totalMoney / (NumberOfDishes + ArrTime);
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


//void Order::SetDistance(int d)
//{
//	Distance = d>0?d:0;
//}

//int Order::GetDistance() const
//{
//	return Distance;
//}

int Order::getNumberOfDishes()
{
	return NumberOfDishes ;
}

int Order::getArrtime()
{
	return ArrTime;
}

int Order::getFinishTime()
{
	return FinishTime;
}

int Order::getServTime()
{
	return ServTime;
}

int Order::getWaitTime()
{
	return waitingTime;
}

void Order::setFinishTime(int t)
{
	FinishTime = t;
}

void Order::setServTime(int t)
{
	ServTime = t;
}

void Order::setWaitTime(int t)
{
	waitingTime = t-ArrTime;
}

double Order::getmoney()
{
	return totalMoney;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

int Order::getSize()
{
	return NumberOfDishes ;
}

double Order::getPriority()
{
	return priority;
}

void Order:: setPriority()
{
	//priority = totalMoney / (NumberOfDishes + ArrTime);
}

