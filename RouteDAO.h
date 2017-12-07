//#pragma once
#ifndef __ROUTEDAO_H
#define __ROUTEDAO_H

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "Route.h"
#include "Order.h"

#include <stdlib.h>
#include <iostream>
#include <vector>


class RouteDAO{
public:
	sql::Driver *driver;
	sql::Connection *con;

	RouteDAO();
	~RouteDAO();

	Route* CreateRoute(Route* r);
	void CreatePoint(int routeID, int pointNum, Point3D p);

	int getRouteCount();
	
	Route* ReadRoute(int id);

	Route* UpdateRoute(int id, int newStatus);

	void DeleteRoute(int id);

	std::vector<Route*> getRoutes();
	std::vector<Point3D> RouteDAO::getPoints(int id);
};

#endif