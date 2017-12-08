#include "stdafx.h"
#include "DroneManager.h"



DroneManager::DroneManager() {
	for (int i = 0; i < DRONENUM; i++) {
		Drone* drone = new Drone();
		Drones.push_back(drone);
	}
}

DroneManager::DroneManager(int d) {
	for (int i = 0; i < d; i++) {
		Drone* drone = new Drone();
		Drones.push_back(drone);
	}
}

DroneManager::~DroneManager() {
}

void DroneManager::run() {
	WriteDrones();

	//while (1) {//TODO: while !completed
		CheckStatuses();
	//}
}

void DroneManager::UpdateStatus() {
}

void DroneManager::WriteDrones() {
}

void DroneManager::CheckStatuses() {
}

void DroneManager::HealthCheck() {
}

void DroneManager::writeDatabase(std::string file){

}
