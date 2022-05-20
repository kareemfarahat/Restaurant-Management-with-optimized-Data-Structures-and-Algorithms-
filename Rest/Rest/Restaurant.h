#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\NormalCook.h"
#include "..\VeganCook.h"
#include "Cook.h"
#include "..\VipCook.h"
#include "..\Generic_DS\LinkedList.h"


#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	int NormalCookscount = 0;
	int VeganCookscount = 0;
	int VipCookscount = 0;
	int NormalOrdercount = 0;
	int VeganOrdercount = 0;
	int VipOrdercount = 0;
	int AutoPromotion;
	int promotedOrdes = 0;
	LinkedList<Order*> Inservice;
	LinkedList<Order*> Finished;
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	// Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	Queue<Order*> Normal_Queue;
	LinkedList <Order*> Vip_Queue;
	Queue<Order*>  Vegan_Queue;
	//
	// TODO: Add More Data Members As Needed
	//
	
	NormalCook* Nptr ;
	VeganCook* Gptr ;
	VipCook* Vptr;
	

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	


	void FillDrawingList(int);

	//
	// TODO: Add More Member Functions As Needed
	//


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void AddtoNormalQueue(Order* po);
	void AddtoVipQueue(Order* po);
	void AddtoVeganQueue(Order* po);
	bool Cancel(int);
	void deleteOrder(int);
	bool IsWaiting(int);
	bool Promote(int,double);
	void InterActive(); 
	void StepByStep();
	void Silent();
	bool AssignToCook(Order*,int);
    VeganCook* GetAvilableVegan(int);
	NormalCook* GetAvilableNormal(int);
	VipCook* GetAvilableVip(int);
	void ToServesList(Order*);
	void ToFinishList(int);
	void AutoPromote(int);
	void printFile(string);
/// ================================================================================================== 

	void Load(std::string);

};

#endif