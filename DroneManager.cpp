#include "stdafx.h"
#include "DroneManager.h"



std::vector<Route*> DroneManager::getRoutesByStatus(int status){
	return rm->getRoutesByStatus(status);
}

DroneManager::DroneManager() {
	targetDroneNum = DRONENUM;
	DAO = new DroneDAO();
}

DroneManager::DroneManager(OrderManager * o, RouteManager * r){
	om = o;
	rm = r;

	targetDroneNum = DRONENUM;
	DAO = new DroneDAO();
}

DroneManager::DroneManager(size_t d) {
	targetDroneNum = d;
	DAO = new DroneDAO();
}

DroneManager::~DroneManager() {
}

void DroneManager::run() {
	CreateDrones();

	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(TICKTIME));

		DistributeRoutes();
		HealthCheck();
		writeDatabase("DailyDrones.csv");
	}
}

void DroneManager::UpdateStatus(int DroneID, int newStatus) {
	switch (newStatus) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		//set Order to loading
		break;
	case 4:
		//set Order to en route
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		//set Order to failed
		break;
	}

	DAO->UpdateRoute(DroneID, newStatus);
}

void DroneManager::Delivered(int DroneID){
	//set order to Complete
	DAO->UpdateRoute(DroneID, 6);
}

void DroneManager::CreateDrones() {
	unsigned int actualNum = DAO->getDroneCount();
	size_t difference = targetDroneNum - actualNum;

	for (; difference != 0; difference--) {
		Drone * d = new Drone(1);
		DAO->CreateDrone(d);
	}
}

void DroneManager::DistributeRoutes(){
	std::vector<Drone*> drones = DAO->getDronesByStatus(1);
	std::vector<Route*> routes = getRoutesByStatus(2);//TODO add failed orders?
	int i = 0;
	while (i < drones.size() && i < routes.size()) {
		drones[i]->route = *routes[i];
		DAO->UpdateRoute(drones[i]);
		i++;
	}
}


void DroneManager::HealthCheck() {//TODO should be done with separate threads
	std::vector<Drone*> drones = DAO->getDrones();
	for (int i = 0; i < drones.size(); i++) {
		std::string command;
		switch (drones[i]->Status) {
		case 1:
			//charge drone
			command = "C:\\Users\\Alex\\Desktop\\College\\Senior Project 2\\DroneProcess\\Release\\DroneProcess.exe" + drones[i]->ID;
			command += " ";
			command += drones[i]->Status;
			command += " ";
			command += drones[i]->OrderKey;
			command += " ";
			command += CHARGETIME;
			system(command.c_str());
			break;
		case 2:
			//wait to distribute routes
			break;
		case 3:
			//send loading
			command = "C:\\Users\\Alex\\Desktop\\College\\Senior Project 2\\DroneProcess\\Release\\DroneProcess.exe" + drones[i]->ID;
			command += " ";
			command += drones[i]->Status;
			command += " ";
			command += drones[i]->OrderKey;
			command += " ";
			command += LOADTIME;
			system(command.c_str());
			break;
		case 4:
			//send en route
			command = "C:\\Users\\Alex\\Desktop\\College\\Senior Project 2\\DroneProcess\\Release\\DroneProcess.exe" + drones[i]->ID;
			command += " ";
			command += drones[i]->Status;
			command += " ";
			command += drones[i]->OrderKey;
			command += " ";
			command += ROUTETIME;
			system(command.c_str());
			break;
		case 5:
			//send delivering
			command = "C:\\Users\\Alex\\Desktop\\College\\Senior Project 2\\DroneProcess\\Release\\DroneProcess.exe" + drones[i]->ID;
			command += " ";
			command += drones[i]->Status;
			command += " ";
			command += drones[i]->OrderKey;
			command += " ";
			command += DELIVERTIME;
			system(command.c_str());
			break;
		case 6:
			//send returning
			command = "C:\\Users\\Alex\\Desktop\\College\\Senior Project 2\\DroneProcess\\Release\\DroneProcess.exe" + drones[i]->ID;
			command += " ";
			command += drones[i]->Status;
			command += " ";
			command += drones[i]->OrderKey;
			command += " ";
			command += ROUTETIME;
			system(command.c_str());
			break;
		case 7:
			//crashed do nothing //TODO have this do something at some point
			break;
		default:
			break;
		}
	}
}

Drone * DroneManager::assembly2ndStep(Drone* d){
	Order* o = om->ReadOrder(d->OrderKey);
	Route* r = rm->ReadRoute(d->RouteKey);
	d->assembly2ndStep(o, r);
	return d;
}

void DroneManager::writeDatabase(std::string file){
	std::ofstream outputFile(file);
	if (outputFile.is_open()) {
		outputFile << "DroneID,";
		outputFile << "OrderKey,";
		outputFile << "RoutesKey,";
		outputFile << "DroneStatusKey";
		outputFile << "\n";

		std::vector<Drone*> temp = DAO->getDrones();
		for (int i = 0; i < temp.size(); i++) {
			outputFile << temp[i]->ID;
			outputFile << ",";
			outputFile << temp[i]->OrderKey;
			outputFile << ",";
			outputFile << temp[i]->RouteKey;
			outputFile << ",";
			outputFile << temp[i]->Status;
			outputFile << "\n";
		}

		outputFile.close();
	}
}
