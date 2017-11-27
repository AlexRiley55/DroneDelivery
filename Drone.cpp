#include "stdafx.h"
#include "Drone.h"

Drone::Drone(){

}

Drone::Drone(int DroneID){
	//TODO: take in info from database
}

Drone::Drone(Drone& other){
	ID = other.ID; //TODO: change these to claim a new ID
	//OrderID
	//RouteID

	//order = other.order;//TODO: do this in order
	//route = other.route;//TODO: do this in order
	//droneStatus;
}

Drone::~Drone(){

}

Drone* Drone::operator= (const Drone& i){
	Drone* tmp = new Drone();
	tmp->ID = i.ID;
	tmp->OrderID = i.OrderID;
	tmp->RouteID = i.RouteID;
	//tmp->order = i.order; //TODO: do this
	//tmp->route = i.route; //TODO: do this
	tmp->droneStatus = i.droneStatus;//will this work?

	return tmp;
}

void Drone::Deliver(){

}

void Drone::Return(){

}

void Drone::gotoNextPoint(){

}

void Drone::gotoPoint(Point3D& p){

}

void Drone::Land(){

}

void Drone::DropPackage(){

}

void Drone::PickupPackage(){

}