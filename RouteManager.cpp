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
	std::vector<Order*> orders = om->getInitialOrders();
	for (unsigned int i = 0; i < orders.size(); i++) {
		DAO->CreateRoute(CalculateRoute(orders[i]));
	}
}

Route* RouteManager::CalculateRoute(Order* o){
	
	std::vector<Point3D> points;
	points.push_back(o->source);
	//TODO: other stuff goes here
	points.push_back(o->dest);
	
	return new Route(o->ID, points);
}

void RouteManager::writeDatabase(std::string file){
	std::ofstream outputFile(file);
	if (outputFile.is_open()) {
		outputFile << "OrderID,";
		outputFile << "SrcX,";
		outputFile << "SrcY,";
		outputFile << "SrcZ,";
		outputFile << "DestX,";
		outputFile << "DestY,";
		outputFile << "DestZ,";
		outputFile << "StatusKey,";
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

