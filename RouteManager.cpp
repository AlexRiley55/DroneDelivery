#include "stdafx.h"
#include "RouteManager.h"



RouteManager::RouteManager(){
	DAO = new RouteDAO();
}

RouteManager::RouteManager(OrderManager * o){
	DAO = new RouteDAO();
	om = o;
}


RouteManager::~RouteManager(){
}

void RouteManager::run(){
	std::vector<Order*> orders = om->getInitalOrders();
	for (unsigned int i = 0; i < orders.size(); i++) {
		CalculateRoute(orders[i]);
	}
}

Route* RouteManager::CalculateRoute(Order* o){
	
	std::vector<Point3D> points;
	points.push_back(o->source);
	//TODO: other stuff goes here
	points.push_back(o->dest);
	
	return new Route(o->ID, points);
}
