#include "stdafx.h"
#include "DroneDAO.h"


DroneDAO::DroneDAO(){

}


DroneDAO::~DroneDAO(){

}

Drone * DroneDAO::CreateDrone(Drone * r){
	return nullptr;
}

int DroneDAO::getDroneCount(){
	return 0;
}

Drone * DroneDAO::ReadRoute(int id){
	return nullptr;
}

Drone * DroneDAO::UpdateRoute(int id, int newStatus){
	return nullptr;
}

void DroneDAO::DeleteRoute(int id){

}

std::vector<Route*> DroneDAO::getDrones(){
	return std::vector<Route*>();
}
