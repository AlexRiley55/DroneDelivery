#include "stdafx.h"
#include <cstdio>
#include "Order.h"
#include "OrderDAO.h"
#include "RouteDAO.h"
#include "OrderManager.h"
#include "RouteManager.h"
#include "Delivery.h"

Order* testOrder();
Route* testRoute();

int main(void) {
	/*
	OrderDAO* od = new OrderDAO();
	Order* o = testOrder();
	od->CreateOrder(o);
	od->getOrderCount();
	*/

	/*
	RouteDAO* rd = new RouteDAO();
	Route* r1 = testRoute();
	Route* r2 = testRoute();
	r2->OrderKey = 2;
	rd->CreateRoute(r1);
	rd->CreateRoute(r2);
	rd->getRouteCount();
	*/

	/*
	OrderManager* om = new OrderManager();

	std::cout << om->fileName << "\n";

	//Order* to = testOrder();
	//om->CreateOrder(to);

	om->run();
	om->writeDatabase("DailyOrders.csv");

	RouteManager* rm = new RouteManager(om);
	rm->run();
	rm->writeDatabase("DailyRoutes.csv");
	*/

	Delivery d;

	d.Activate();

	system("pause");
}

Order* testOrder() {
	Point3D s(1,2,3);
	Point3D e(4, 5, 6);
	Order* o = new Order(1, s, e, 9);
	return o;
}

Route* testRoute() {
	Point3D s(1, 2, 3);
	Point3D p1(4, 5, 6);
	Point3D p2(7, 8, 9);
	Point3D p3(10, 11, 12);
	Point3D e(13, 14, 15);
	std::vector<Point3D> routes;
	routes.push_back(s);
	routes.push_back(p1);
	routes.push_back(p2);
	routes.push_back(p3);
	routes.push_back(e);
	Route* r = new Route(1,routes);
	return r;
}