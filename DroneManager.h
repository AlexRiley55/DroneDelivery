#ifndef __DRONEMANAGER_H
#define __DRONEMANAGER_H

#define DRONENUM 6

#include "Manager.h"
#include "Drone.h"
#include <vector>

class DroneManager : public Manager {
public:
	DroneManager();
	DroneManager(int d);
	~DroneManager();

	std::vector<Drone*> Drones;

	void run();
	void UpdateStatus();
	void WriteDrones();
	void CheckStatuses();
	void HealthCheck();

	void writeDatabase(std::string file);
};

#endif // !__DRONEMANAGER_H