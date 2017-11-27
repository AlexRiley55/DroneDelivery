//#pragma once
#ifndef __DRONE_H
#define __DRONE_H
#include "Order.h"
#include "Route.h"

class Drone
{
	enum DroneStatusEnum; //TODO: put this in a header somewhere?
public:
	int ID, OrderID, RouteID;
	Order order;
	Route route;
	DroneStatusEnum droneStatus;

	Drone();
	Drone(int DroneID);
	Drone(Drone& other);
	~Drone();

	Drone* operator= (const Drone& i);

	void Deliver();
	void Return();

	void gotoNextPoint();
	void gotoPoint(Point3D& p);

	void Land();
	void DropPackage();
	void PickupPackage();
};

#endif