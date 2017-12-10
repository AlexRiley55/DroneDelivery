#ifndef __DRONEMANAGER_H
#define __DRONEMANAGER_H

#define DRONENUM 6

#include "Manager.h"
#include "OrderManager.h"
#include "RouteManager.h"
#include "DroneDAO.h"
#include "Drone.h"
#include <vector>

class DroneManager : public Manager {
private:
	size_t targetDroneNum;
	std::vector<Route*> getRoutesByStatus(int status);

public:
	DroneManager();
	DroneManager(OrderManager* o, RouteManager* r);//TODO great place for a builder patern
	DroneManager(size_t d);
	~DroneManager();

	std::vector<Drone*> Drones;

	void run();
	void UpdateStatus(int DroneID, int newStatus);
	void Delivered(int DroneID);
	void CreateDrones();
	void DistributeRoutes();
	void HealthCheck();

	Drone* assembly2ndStep(Drone* d);

	void writeDatabase(std::string file);

	OrderManager* om;
	RouteManager* rm;

	DroneDAO* DAO;
};

#endif // !__DRONEMANAGER_H