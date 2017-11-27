//#pragma once
#ifndef __ORDER_H
#define __ORDER_H
#include <string>
#include "Point3D.h"

class Order{
private:

public:
	int ID;
	Point3D source;
	Point3D dest;
	int StatusKey;

	Order() {
		//never use this
	}

	Order(int id, Point3D s, Point3D d, int sk){
		ID = id;
		source = s;
		dest = d;
		StatusKey = sk;
	}
	
	Order(Point3D s, Point3D d, int sk){
		source = s;
		dest = d;
		StatusKey = sk;
	}

	Order(Point3D s, Point3D d) {
		source = s;
		dest = d;
		StatusKey = 1;
	}

	//~Order(){}

	Order* operator=(Order& other) {
		ID = other.ID; source = other.source; dest = other.dest; StatusKey = other.StatusKey;
		return this;
	}
};

#endif