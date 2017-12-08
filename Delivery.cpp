#include "stdafx.h"
#include "Delivery.h"

Delivery::Delivery(){
	om = new OrderManager();
	rm = new RouteManager(om);
	dm = new DroneManager(om, rm);
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
	om->writeDatabase("DailyOrders.csv");
}

void Delivery::RunRouteManager(){
	rm->run();
	rm->writeDatabase("DailyRoutes.csv");
}

void Delivery::RunDroneManager(){
	dm->run();
}
