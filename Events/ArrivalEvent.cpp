
#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"
#include"..\Rest\Order.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType , double ordMoney, int size):Event(eTime, oID)
{
	OrdType = oType;
	OrdMoney = ordMoney;
	Size = size;
	
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	
	Order* pOrd = new Order(OrdType, EventTime,OrderID,Size,OrdMoney);
	switch (OrdType)
	{
	case TYPE_NRM:
		pRest->AddtoNormalQueue(pOrd);
		break;
	case TYPE_VIP:
		pRest->AddtoVipQueue(pOrd);
		break;
	case TYPE_VGAN:
		pRest->AddtoVeganQueue(pOrd);
		break;
	
	
	
	}
}
