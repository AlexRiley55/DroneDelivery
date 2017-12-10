//#pragma once
#ifndef __ROUTE_H
#define __ROUTE_H

#include <vector>
#include "Point3D.h"

class Route{
public:
	int OrderKey;
	int ID;
	std::vector<Point3D> Routes;

	Route() {

	}

	Route(int ok, int id, std::vector<Point3D> rts) {//TODO: why is this in a different order then the database
		OrderKey = ok;
		ID = id;
		Routes = rts;
	}

	Route(int ok, std::vector<Point3D> rts) {
		OrderKey = ok;
		Routes = rts;
	}
	
	~Route() {

	}

	Route* operator =(Route& other) {
		OrderKey = other.OrderKey;
		ID = other.ID;
		Routes = other.Routes;
		return this;
	}
};

#endif