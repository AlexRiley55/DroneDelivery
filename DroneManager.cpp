#include "stdafx.h"
#include "DroneManager.h"



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
	 
	//while (1) {//TODO: while !completed
		DistributeRoutes();
	//}
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

}


void DroneManager::HealthCheck() {//TODO should be done with separate threads
}

Drone * DroneManager::assembly2ndStep(Drone* d){
	Order* o = om->ReadOrder(d->OrderKey);
	Route* r = rm->ReadRoute(d->RouteKey);
	d->assembly2ndStep(o, r);
	return d;
}

void DroneManager::writeDatabase(std::string file){

}
