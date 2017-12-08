//#pragma once
#ifndef __DRONE_H
#define __DRONE_H
#include "Order.h"
#include "Route.h"

class Drone
{
	enum DroneStatusEnum; //TODO: put this in a header somewhere?
public:
	int ID, Orderkey, RouteKey, Status;
	Order order;
	Route route;
	int droneStatus;

	Drone();
	Drone(int Ok, int RK, int s);
	Drone(int id, int Ok, int RK, int s);
	Drone(Drone& other);
	~Drone();

	Drone* operator= (const Drone& i);

	void assembly2ndStep(Order o, Route r);

	void Deliver();
	void Return();

	void gotoNextPoint();
	void gotoPoint(Point3D& p);

	void Land();
	void DropPackage();
	void PickupPackage();
};

#endif