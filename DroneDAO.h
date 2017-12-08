//#pragma once
#ifndef __DRONEDAO_H
#define __DRONEDAO_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "Drone.h"

class DroneDAO{
public:
	sql::Driver *driver;
	sql::Connection *con;
	DroneDAO();
	~DroneDAO();

	Drone* CreateDrone(Drone* r);

	int getDroneCount();

	Drone* ReadRoute(int id);

	Drone* UpdateRoute(int id, int newStatus);

	void DeleteRoute(int id);

	std::vector<Drone*> getDrones();
};

#endif

