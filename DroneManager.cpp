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
		CheckStatuses();
	//}
}

void DroneManager::UpdateStatus() {
}

void DroneManager::CreateDrones() {
	unsigned int actualNum = DAO->getDroneCount();
	size_t difference = targetDroneNum - actualNum;

	for (; difference != 0; difference--) {
		Drone * d = new Drone(1);
		DAO->CreateDrone(d);
	}
}

void DroneManager::CheckStatuses() {
}

void DroneManager::HealthCheck() {
}

Drone * DroneManager::assembly2ndStep(Drone* d){
	Order* o = om->ReadOrder(d->OrderKey);
	Route* r = rm->ReadRoute(d->RouteKey);
	d->assembly2ndStep(o, r);
	return d;
}

void DroneManager::writeDatabase(std::string file){

}
