#ifndef __ROUTEMANAGER_H
#define __ROUTEMANAGER_H

#include "Manager.h"
#include "Route.h"
#include "RouteDAO.h"
#include "OrderManager.h"
#include <algorithm>

class RouteManager : public Manager{
private:
	RouteManager();
public:
	RouteManager(OrderManager* o);
	~RouteManager();

	void run();

	Route* CalculateRoute(Order* o);

	void writeDatabase(std::string file);

	RouteDAO* DAO;
	OrderManager* om;
};

#endif // !__ROUTEMANAGER_H
