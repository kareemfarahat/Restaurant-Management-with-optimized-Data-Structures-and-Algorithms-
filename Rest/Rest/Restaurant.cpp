#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\NormalCook.h"
#include "..\VeganCook.h"
#include "Cook.h"
#include "..\VipCook.h"
#include "..\Events\PromotionEvent.h"
#include "..\Events\CancelEvent.h"

Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		InterActive();
		break;
	case MODE_STEP:
		StepByStep();
		break;
	case MODE_SLNT:
		Silent();
		break;

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		if (pGUI)
			delete pGUI;
}

void Restaurant::FillDrawingList(int ctime)
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	int N,v,G,x,y;
	Order** Narr = Normal_Queue.toArray(N);
	Order** Varr = Vip_Queue.ToArray(v);
	Order** Garr = Vegan_Queue.toArray(G);
	Order** Servarr = Inservice.ToArray(x);
	Order** Finishedarr = Finished.ToArray(y);
	
	int Ni =0, Vi = 0, Gi = 0;
	for (int i = 0; i < (N + v + G); i++) {
		if (Narr != nullptr && Varr != nullptr && Garr != nullptr) {
			if ((Narr[Ni]->getArrtime() <= Varr[Vi]->getArrtime()) && (Narr[Ni]->getArrtime() <= Garr[Gi]->getArrtime()))
			{
				pGUI->AddToDrawingList(Narr[Ni]);
				if (Ni < N-1)
					Ni++;
				else
					Narr = nullptr;
			}
			else if (Varr[Vi]->getArrtime() <= Narr[Ni]->getArrtime() && Varr[Vi]->getArrtime() <= Garr[Gi]->getArrtime()) {
				pGUI->AddToDrawingList(Varr[Vi]);
				if (Vi < v-1)
					Vi++;
				else
					Varr = nullptr;
			}
			else if (Garr[Gi]->getArrtime() <= Narr[Ni]->getArrtime() && Garr[Gi]->getArrtime() <= Varr[Vi]->getArrtime()) {
				pGUI->AddToDrawingList(Garr[Gi]);
				if (Gi < G-1)
					Gi++;
				else
					Garr = nullptr;
			}
		}
		else if (Narr != nullptr && Varr != nullptr && Garr == nullptr) {
			if (Narr[Ni]->getArrtime() <= Varr[Vi]->getArrtime()) {
				pGUI->AddToDrawingList(Narr[Ni]);
				if (Ni < N-1)
					Ni++;
				else
					Narr = nullptr;
			}
			else {
				pGUI->AddToDrawingList(Varr[Vi]);
				if (Vi < v-1)
					Vi++;
				else
					Varr = nullptr;
			}
		}
		else if (Narr != nullptr && Varr == nullptr && Garr != nullptr) {
			if (Narr[Ni]->getArrtime() <= Garr[Gi]->getArrtime()) {
				pGUI->AddToDrawingList(Narr[Ni]);
				if (Ni < N-1)
					Ni++;
				else
					Narr = nullptr;
			}
			else {
				pGUI->AddToDrawingList(Garr[Gi]);
				if (Gi < G-1)
					Gi++;
				else
					Garr = nullptr;
			}
		}
		else if (Narr == nullptr && Varr != nullptr && Garr != nullptr) {
			if (Varr[Vi]->getArrtime() <= Garr[Gi]->getArrtime()) {
				pGUI->AddToDrawingList(Varr[Vi]);
				if (Vi < v-1)
					Vi++;
				else
					Varr = nullptr;
			}
			else {
				pGUI->AddToDrawingList(Garr[Gi]);
				if (Gi < G-1)
					Gi++;
				else
					Garr = nullptr;
			}
		}
		else if (Narr != nullptr && Varr == nullptr && Garr == nullptr)
		{
			pGUI->AddToDrawingList(Narr[Ni]);
			if (Ni < N-1)
				Ni++;
			else
				Narr = nullptr;
		}

		else if (Narr == nullptr && Varr != nullptr && Garr == nullptr)
		{
			pGUI->AddToDrawingList(Varr[Vi]);
			if (Vi < v-1)
				Vi++;
			else
				Varr = nullptr;
		}
		else if (Narr == nullptr && Varr == nullptr && Garr != nullptr)
		{
			pGUI->AddToDrawingList(Garr[Gi]);
			if (Gi < G-1)
				Gi++;
			else
				Garr = nullptr;
		}
	}

	for (int i = 0; i < NormalCookscount; i++) {
		if (Nptr[i].IsAvailable(ctime))
			pGUI->AddToDrawingList(&Nptr[i]);
		
		
	}


	for (int i = 0; i < VipCookscount; i++) {
		if (Vptr[i].IsAvailable(ctime))
		pGUI->AddToDrawingList(&Vptr[i]);
	}


	for (int i = 0; i < VeganCookscount; i++) {
		if (Gptr[i].IsAvailable(ctime))
		pGUI->AddToDrawingList(&Gptr[i]);
	}


	for (int i = 0  ; i < x;i++ )
	{
		pGUI->AddToDrawingList(Servarr[i]);
	}


	for (int i = 0; i < y; i++)
	{
		pGUI->AddToDrawingList(Finishedarr[i]);
	}

}




//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 

void Restaurant::AddtoNormalQueue(Order* po)
{
	Normal_Queue.enqueue(po);
}

void Restaurant::AddtoVipQueue(Order* po)
{
	Vip_Queue.InsertEnd(po);
}

void Restaurant::AddtoVeganQueue(Order* po)
{
	Vegan_Queue.enqueue(po);
}

bool Restaurant::Cancel(int x)
{
	if (IsWaiting(x)) {
		Order* X;
		Queue <Order*> fill;
		while (Normal_Queue.dequeue(X)) {

			if (X->GetID() != x) {
				fill.enqueue(X);
			}
			else
				delete X;
		}
		while (fill.dequeue(X)) {

			Normal_Queue.enqueue(X);
		}
		return true;
	}
	else
		return false;
	}

void Restaurant::deleteOrder(int x)
{	
	Order* X;
	Queue <Order*> fill;
	while (Normal_Queue.dequeue(X)) {

		if (X->GetID() != x) {
			fill.enqueue(X);
		}
	}
	while (fill.dequeue(X)) {

		Normal_Queue.enqueue(X);
	}
}


bool Restaurant::IsWaiting(int x)
{
	int sizeN = 0;
	Order** N;
	N =	Normal_Queue.toArray(sizeN);
	for (int i = 0; i < sizeN; i++) {
		if (N[i]->GetID() == x)
			return true;
	}
	
	return false;
}

bool Restaurant::Promote(int x, double m)
{
	int sizeN = 0;
	Order** N;
	N = Normal_Queue.toArray(sizeN);
	for (int i = 0; i < sizeN; i++) {
		if (N[i]->GetID() == x) {
			Order* V = new Order(TYPE_VIP, N[i]->getArrtime(), x, N[i]->getSize(), (N[i]->getmoney() + m));
			Vip_Queue.InsertEnd(V);
			VipOrdercount++;
			NormalOrdercount--;
			deleteOrder(x);
			return true;
		}
	}
		 return false;
}

void Restaurant::InterActive()
{
	
	pGUI->PrintMessage("Enter File Name ");
	
	Load(pGUI->GetString());
	int CurrentTimeStep = 1;
	bool f;
	Order* pOrd,*nOrd;
	while (!EventsQueue.isEmpty()||!Inservice.IsEmpty()|| !Vip_Queue.IsEmpty()|| !Normal_Queue.isEmpty()|| !Vegan_Queue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);
		//////////////////////////////////
		AutoPromote(CurrentTimeStep);

		while (!Vip_Queue.IsEmpty()) {
			pOrd = Vip_Queue.GetPriority();
			if (AssignToCook(pOrd, CurrentTimeStep))
				ToServesList(pOrd);
			else
			{
				Vip_Queue.InsertEnd(pOrd);
				break;
			}
		}

		while (!Normal_Queue.isEmpty() || !Vegan_Queue.isEmpty())
		{
			f = false;
			if (Normal_Queue.peekFront(pOrd) &&
				Vegan_Queue.peekFront(nOrd)) 
			{
				if (pOrd->getArrtime() < nOrd->getArrtime())
				{
					if (AssignToCook(pOrd, CurrentTimeStep))
					{
						ToServesList(pOrd);
						f = true;
					}
				}
				else if (pOrd->getArrtime() > nOrd->getArrtime())
				{
					if (AssignToCook(nOrd, CurrentTimeStep)) 
					{
						ToServesList(nOrd);
						f = true;
					}
				}
				else
				{
					pOrd = pOrd->getmoney() > nOrd->getmoney() ? pOrd : nOrd;
					if (AssignToCook(pOrd, CurrentTimeStep)) 
					{
						ToServesList(pOrd);
						f = true;
					}
				}
				
			}
			else if (!Normal_Queue.peekFront(pOrd) &&
				Vegan_Queue.peekFront(nOrd)) 
			{
				if (AssignToCook(nOrd, CurrentTimeStep))
				{
					ToServesList(nOrd);
					f = true;
				}
			}
			else if (Normal_Queue.peekFront(pOrd) &&
				!Vegan_Queue.peekFront(nOrd))
			{
				if (AssignToCook(pOrd, CurrentTimeStep))
				{
					ToServesList(pOrd);
					f = true;
				}
			}
			if (!f)
				break;
		}
		
		///////////////////////////////////
		ToFinishList(CurrentTimeStep);
		
					
		//////////////////////////////////
		
		FillDrawingList(CurrentTimeStep);

		pGUI->UpdateInterface();
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
		
	}
	pGUI->PrintMessage("Please enter output file name ");
	string S = pGUI->GetString();
	printFile(S);
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}
void Restaurant::StepByStep()
{
	pGUI->PrintMessage("Enter File Name ");

	Load(pGUI->GetString());
	int CurrentTimeStep = 1;
	bool f;
	Order* pOrd, * nOrd;
	while (!EventsQueue.isEmpty() || !Inservice.IsEmpty() || !Vip_Queue.IsEmpty() || !Normal_Queue.isEmpty() || !Vegan_Queue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);
		//////////////////////////////////
		AutoPromote(CurrentTimeStep);

		while (!Vip_Queue.IsEmpty()) {
			pOrd = Vip_Queue.GetPriority();
			if (AssignToCook(pOrd, CurrentTimeStep))
				ToServesList(pOrd);
			else
				break;
		}

		while (!Normal_Queue.isEmpty() || !Vegan_Queue.isEmpty())
		{
			f = false;
			if (Normal_Queue.peekFront(pOrd) &&
				Vegan_Queue.peekFront(nOrd))
			{
				if (pOrd->getArrtime() < nOrd->getArrtime())
				{
					if (AssignToCook(pOrd, CurrentTimeStep))
					{
						ToServesList(pOrd);
						f = true;
					}
				}
				else if (pOrd->getArrtime() > nOrd->getArrtime())
				{
					if (AssignToCook(nOrd, CurrentTimeStep))
					{
						ToServesList(nOrd);
						f = true;
					}
				}
				else
				{
					pOrd = pOrd->getmoney() > nOrd->getmoney() ? pOrd : nOrd;
					if (AssignToCook(pOrd, CurrentTimeStep))
					{
						ToServesList(pOrd);
						f = true;
					}
				}

			}
			else if (!Normal_Queue.peekFront(pOrd) &&
				Vegan_Queue.peekFront(nOrd))
			{
				if (AssignToCook(nOrd, CurrentTimeStep))
				{
					ToServesList(nOrd);
					f = true;
				}
			}
			else if (Normal_Queue.peekFront(pOrd) &&
				!Vegan_Queue.peekFront(nOrd))
			{
				if (AssignToCook(pOrd, CurrentTimeStep))
				{
					ToServesList(pOrd);
					f = true;
				}
			}
			if (!f)
				break;
		}

		///////////////////////////////////
		ToFinishList(CurrentTimeStep);


		//////////////////////////////////

		FillDrawingList(CurrentTimeStep);

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();

	}
	pGUI->PrintMessage("Please enter output file name ");
	string S = pGUI->GetString();
	printFile(S);
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}
void Restaurant::Silent()
{
	pGUI->PrintMessage("Enter File Name ");

	Load(pGUI->GetString());
	int CurrentTimeStep = 1;
	bool f;
	Order* pOrd, * nOrd;
	while (!EventsQueue.isEmpty() || !Inservice.IsEmpty() || !Vip_Queue.IsEmpty() || !Normal_Queue.isEmpty() || !Vegan_Queue.isEmpty())
	{

		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);
		ExecuteEvents(CurrentTimeStep);
		//////////////////////////////////
		AutoPromote(CurrentTimeStep);

		while (!Vip_Queue.IsEmpty()) {
			pOrd = Vip_Queue.GetPriority();
			if (AssignToCook(pOrd, CurrentTimeStep))
				ToServesList(pOrd);
			else
				break;
		}

		while (!Normal_Queue.isEmpty() || !Vegan_Queue.isEmpty())
		{
			f = false;
			if (Normal_Queue.peekFront(pOrd) &&
				Vegan_Queue.peekFront(nOrd))
			{
				if (pOrd->getArrtime() < nOrd->getArrtime())
				{
					if (AssignToCook(pOrd, CurrentTimeStep))
					{
						ToServesList(pOrd);
						f = true;
					}
				}
				else if (pOrd->getArrtime() > nOrd->getArrtime())
				{
					if (AssignToCook(nOrd, CurrentTimeStep))
					{
						ToServesList(nOrd);
						f = true;
					}
				}
				else
				{
					pOrd = pOrd->getmoney() > nOrd->getmoney() ? pOrd : nOrd;
					if (AssignToCook(pOrd, CurrentTimeStep))
					{
						ToServesList(pOrd);
						f = true;
					}
				}

			}
			else if (!Normal_Queue.peekFront(pOrd) &&
				Vegan_Queue.peekFront(nOrd))
			{
				if (AssignToCook(nOrd, CurrentTimeStep))
				{
					ToServesList(nOrd);
					f = true;
				}
			}
			else if (Normal_Queue.peekFront(pOrd) &&
				!Vegan_Queue.peekFront(nOrd))
			{
				if (AssignToCook(pOrd, CurrentTimeStep))
				{
					ToServesList(pOrd);
					f = true;
				}
			}
			if (!f)
				break;
		}

		///////////////////////////////////
		ToFinishList(CurrentTimeStep);
		//////////////////////////////////
		CurrentTimeStep++;	//advance timestep

	}
	pGUI->PrintMessage("Please enter output file name ");
	string S = pGUI->GetString();
	printFile(S);
    pGUI->PrintMessage("generation done, click to END program");
    pGUI->waitForClick();

}
bool Restaurant::AssignToCook(Order* ord,int ctime)
{
	NormalCook* N;
	VipCook* V;
	VeganCook* G;
	switch (ord->GetType())
	{
	case TYPE_NRM:
	    N = GetAvilableNormal(ctime);
		if (N) {
			N->setTimeToFinish(ord,ctime);
			N->setType(TYPE_NRM);
			ord->setFinishTime(N->GetFinishTime());
			ord->setServTime(N->GetFinishTime()-ctime);
			ord->setWaitTime(ctime);
			//ToServesList(ord);
			return true;
		}
	    V = GetAvilableVip(ctime);
		if (V) {
			V->setTimeToFinish(ord, ctime);
			V->setType(TYPE_VIP);
			ord->setFinishTime(V->GetFinishTime());
			ord->setServTime(V->GetFinishTime() - ctime);
			ord->setWaitTime(ctime);
			//ToServesList(ord);

			return true;
		}
		return false;
		break;

	case TYPE_VIP:
		 V = GetAvilableVip(ctime);
		if (V) {
			V->setTimeToFinish(ord, ctime);
			V->setType(TYPE_VIP);
			ord->setFinishTime(V->GetFinishTime());
			ord->setServTime(V->GetFinishTime() - ctime);
			ord->setWaitTime(ctime);
			//ToServesList(ord);

			return true;
		}
		 N = GetAvilableNormal(ctime);
		if (N) {
			N->setTimeToFinish(ord, ctime);
			N->setType(TYPE_NRM);
			ord->setFinishTime(N->GetFinishTime());
			ord->setServTime(N->GetFinishTime() - ctime);
			ord->setWaitTime(ctime);
			//ToServesList(ord);

			return true;
		}
		 G = GetAvilableVegan(ctime);
		if (G) {
			G->setTimeToFinish(ord, ctime);
			G->setType(TYPE_VGAN);
			ord->setFinishTime(G->GetFinishTime());
			ord->setServTime(G->GetFinishTime() - ctime);
			ord->setWaitTime(ctime);
			//ToServesList(ord);

			return true;
		}
		return false;
		break;


	case TYPE_VGAN:
		 G = GetAvilableVegan(ctime);
		if (G) {
			G->setTimeToFinish(ord, ctime);
			G->setType(TYPE_VGAN);
			ord->setFinishTime(G->GetFinishTime());
			ord->setServTime(G->GetFinishTime() - ctime);
			ord->setWaitTime(ctime);
//			ToServesList(ord);

			return true;
		}
		return false;
		break;

	}
}
VeganCook* Restaurant::GetAvilableVegan(int ctime)
{
	
	for (int i = 0; i < VeganCookscount; i++) {
		if (Gptr[i].IsAvailable(ctime))
			return &Gptr[i];
	}
	return nullptr;
}
NormalCook* Restaurant::GetAvilableNormal(int ctime)
{
	for (int i = 0; i < NormalCookscount; i++) {
		if (Nptr[i].IsAvailable(ctime))
			return &Nptr[i];
	}
	return nullptr;
}
VipCook* Restaurant::GetAvilableVip(int ctime)
{
	for (int i = 0; i < VipCookscount; i++) {
		if (Vptr[i].IsAvailable(ctime))
			return &Vptr[i];
	}
	return nullptr;
}
void Restaurant::ToServesList(Order* pOrd)
{
	switch (pOrd->GetType())
	{
	case TYPE_NRM:
		Order* N;
		Normal_Queue.dequeue(N);
		Inservice.InsertEnd(N);
		pOrd->setStatus(SRV);
		break;
	case TYPE_VGAN:
		Order* G;
		Vegan_Queue.dequeue(G);
		Inservice.InsertEnd(G);
		pOrd->setStatus(SRV);
		break;
	case TYPE_VIP:

		Inservice.InsertEnd(pOrd);
		Vip_Queue.DeleteNode(pOrd);
		pOrd->setStatus(SRV);
		break;
	default:
		break;
	}
}
void Restaurant::ToFinishList(int ctime)
{
	/*int i = 0;
	Order** p = Inservice.getNodes(ctime);
	while (p && p[i] != nullptr) {
		Finished.InsertEnd(p[i]);
		p[i]->setStatus(DONE);
		delete p[i];
		i++;
	}
	if(p)
	delete p[i];*/
	int length;
	Order** p = Inservice.ToArray(length);
	for (int i = 0; i < length; i++)
	{
		if (p[i]->getFinishTime() == ctime)
		{
			p[i]->setStatus(DONE);
			Finished.InsertEnd(p[i]);
			Inservice.DeleteNode(p[i]);
		}
	}
		
}

void Restaurant::AutoPromote(int ctime)
{
	Order* pOrd;
	while (!Normal_Queue.isEmpty())
	{
		Normal_Queue.peekFront(pOrd);
		if ((ctime - pOrd->getArrtime()) > AutoPromotion)
		{
			Promote(pOrd->GetID(), 0);
			promotedOrdes++;
		}
		else
			return;
	}
}
void Restaurant::printFile(string s)
{
	ofstream file(s);
	file << "FT		ID		AT		WT		ST\n";
	int Length, c = 0;
	double tw = 0, ts = 0;
	
	Order** p = Finished.ToArray(Length);
	Order* ord;
	for (int i = 0; i < Length; i++)
	{

			for (int j = 1; j < Length; j++) {
				if (p[i]->getFinishTime() != p[j]->getFinishTime())
					break;
				else if (p[i]->getServTime() > p[j]->getServTime())
				{
					ord = p[j];
					p[j] = p[i];
					p[i] = ord;
				}
				
			}
		
		tw += p[i]->getWaitTime();
		ts += p[i]->getServTime();
		file << p[i]->getFinishTime() << "		" << p[i]->GetID() << "		" << p[i]->getArrtime()
		 << "		" << p[i]->getWaitTime() << "		" << p[i]->getServTime() << "		" << endl;

	}
	file << "----------------------------------------------------" << endl;
	file << "Orders: " << (NormalOrdercount + VipOrdercount + VeganOrdercount)
		<< " [Norm: " << NormalOrdercount << ", Veg: " << VeganOrdercount 
		<< ", VIP: " << VipOrdercount << " ]" << endl;
	file << "Cooks: " << (NormalCookscount + VipCookscount + VeganCookscount)
		<< " [Norm: " << NormalCookscount << ", Veg: " << VeganCookscount
		<< ", VIP: " << VipCookscount << " ]" << endl;
	file << "Avg Wait = " << tw / Length << " ,  Avg Serv = " << ts / Length << endl;
	
	file << "Auto promoted: " << promotedOrdes << endl;

}
////////////////////////////////////////////////





void Restaurant::Load(std::string file) {
	int  SN, SG, SV, BO, BN, BV, BG ;
	char Type, Order;
	int NumEvents;
	int Arrival, ID, Size,  ExMony;
	double Mony;
	Event* Eptr;
	std::fstream Data;
	Data.open(file);
	if (Data.is_open()) {
		Data >> NormalCookscount >> VeganCookscount >> VipCookscount >> SN >> SG >> SV >> BO >> BN >> BG >> BV;
		
		 Nptr = new NormalCook[NormalCookscount];
		for (int i = 0; i < NormalCookscount ; i++) {
			Nptr[i].setID(i+1);
			Nptr[i].setSpeed(SN);
			Nptr[i].setBreakDuration(BN);
			Nptr[i].setBreakLimit(BO);
		}
		
		Gptr = new VeganCook[VeganCookscount];
		for (int i = 0; i < VeganCookscount; i++) {

			Gptr[i].setID(200+i);
			Gptr[i].setSpeed(SG);
			Gptr[i].setBreakDuration(BG);
			Gptr[i].setBreakLimit(BO);
			
		}
		Vptr = new VipCook[VipCookscount];
		for (int i = 0; i < VipCookscount; i++) {
			Vptr[i].setID( 400 + i);
			Vptr[i].setSpeed(SV);
			Vptr[i].setBreakDuration(BV);
			Vptr[i].setBreakLimit(BO);
			
			
		}
	}
	else
	{
		pGUI->PrintMessage("Failed to open file...., please enter file name again, click for enter correct file name");
		pGUI->UpdateInterface();
		pGUI->waitForClick();
		PROG_MODE	mode = pGUI->getGUIMode();

		switch (mode)	
		{
		case MODE_INTR:
			InterActive();
			break;
		case MODE_STEP:
			StepByStep();
			break;
		case MODE_SLNT:
			Silent();
			break;
		};
	}



	Data >> AutoPromotion >> NumEvents;
	while (!Data.eof())
	{
		Data >> Type;
		switch (Type) {
		case 'R':
			Data >> Order >> Arrival >> ID >> Size >> Mony;
			if (Order == 'N') {
				Eptr = new ArrivalEvent(Arrival, ID, TYPE_NRM, Mony, Size);
				EventsQueue.enqueue(Eptr);
				NormalOrdercount++;
			}
			else if (Order == 'G') {
				Eptr = new ArrivalEvent(Arrival, ID, TYPE_VGAN, Mony, Size);
				EventsQueue.enqueue(Eptr);
				VeganOrdercount++;
			}
			else  {
				Eptr = new ArrivalEvent(Arrival, ID, TYPE_VIP, Mony, Size);
				EventsQueue.enqueue(Eptr);
				VipOrdercount++;
			}
			break;

		case 'P':
			Data >> Arrival >> ID >> ExMony;
			Eptr = new PromotionEvent(Arrival, ID, ExMony);
			EventsQueue.enqueue(Eptr);
			
			break;

		case 'X':
			Data >> Arrival >> ID;
			Eptr = new CancelEvent(Arrival, ID);
			EventsQueue.enqueue(Eptr);
			break;

		}
	}

	Data.close();
}
