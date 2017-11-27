#include "stdafx.h"
#include "Delivery.h"



Delivery::Delivery(){
	om = new OrderManager();
	rm = new RouteManager(om);
	dm = new DroneManager();
}


Delivery::~Delivery(){
}

void Delivery::Activate(){
	RunOrderManager();
	RunRouteManager();
	RunDroneManager();
}

void Delivery::RunOrderManager(){
	om->run();
}

void Delivery::RunRouteManager(){
	rm->run();
}

void Delivery::RunDroneManager(){
	dm->run();
}
