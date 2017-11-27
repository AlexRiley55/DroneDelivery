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

	Route(int ok, int rpk, std::vector<Point3D> rts) {
		OrderKey = ok;
		ID = rpk;
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
		Routes = other.Routes;
		return this;
	}
};

#endif