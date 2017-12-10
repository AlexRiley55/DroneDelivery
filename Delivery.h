#ifndef __DELIVERY_H
#define __DELIVERY_H

#include "OrderManager.h"
#include "RouteManager.h"
#include "DroneManager.h"

#include <random>
#include <time.h>

class Delivery{//TODO should be a singleton
public:
	Delivery();
	~Delivery();
	
	void Activate();

	void RunOrderManager();
	void RunRouteManager();
	void RunDroneManager();

	OrderManager* om;
	RouteManager* rm;
	DroneManager* dm;
};

#endif // !__DELIVERY_H