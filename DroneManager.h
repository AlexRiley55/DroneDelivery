#ifndef __DRONEMANAGER_H
#define __DRONEMANAGER_H

#include "Manager.h"

class DroneManager : public Manager{
public:
	DroneManager();
	~DroneManager();

	void run();
	void UpdateStatus();
	void WriteDrones();
	void CheckStatuses();
	void HealthCheck();
};

#endif // !__DRONEMANAGER_H