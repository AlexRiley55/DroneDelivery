#include "stdafx.h"
#include "RouteManager.h"



RouteManager::RouteManager(){
	DAO = new RouteDAO();
}

void RouteManager::updateOrder(int id, int status){
	om->updateOrder(id, status);
}

RouteManager::RouteManager(OrderManager * o){
	DAO = new RouteDAO();
	om = o;
}


RouteManager::~RouteManager(){
}

void RouteManager::run(){
	std::vector<Order*> orders = om->getOrdersByStatus(1);//get initial orders
	for (unsigned int i = 0; i < orders.size(); i++) {
		Order* o = orders[i];
		DAO->CreateRoute(CalculateRoute(o));
		updateOrder(o->ID, 2);
	}
}

Route* RouteManager::CalculateRoute(Order* o){
	
	std::vector<Point3D> points;
	points.push_back(o->source);
	//TODO: other stuff goes here
	Point3D p;
	p.randomize();
	points.push_back(p);
	points.push_back(o->dest);
	
	return new Route(o->ID, points);
}

void RouteManager::writeDatabase(std::string file){
	std::ofstream outputFile(file);
	if (outputFile.is_open()) {
		outputFile << "RouteID,";
		outputFile << "OrderKey,";
		outputFile << "X,";
		outputFile << "Y,";
		outputFile << "Z,";
		outputFile << "\n";

		std::vector<Route*> temp = getRoutes();
		for (int i = 0; i < temp.size(); i++) {
			outputFile << temp[i]->ID;
			outputFile << ",";
			outputFile << temp[i]->OrderKey;
			outputFile << ",";
			for (int j = 0; j < temp[i]->Routes.size(); j++) {
				Point3D tmp = temp[i]->Routes[j];
				outputFile << tmp.x;
				outputFile << ",";
				outputFile << tmp.y;
				outputFile << ",";
				outputFile << tmp.z;
				outputFile << ",";
			}

			outputFile << "\n";
		}

		outputFile.close();
	}
}

std::vector<Route*> RouteManager::getRoutes(){
	return DAO->getRoutes();
}

std::vector<Route*> RouteManager::getRoutesByStatus(int status){
	return DAO->getRoutesByStatus(status);
}

Route * RouteManager::ReadRoute(int id){
	return DAO->ReadRoute(id);
}

