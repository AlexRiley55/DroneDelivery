//#pragma once
#ifndef __Point3D_H
#define __Point3D_H

#include <random>

class Point3D
{
public:
	Point3D(){}
	Point3D(int X, int Y, int Z) { x = X; y = Y; z = Z; }
	~Point3D(){}

	int x;
	int y;
	int z;

	Point3D* operator = (Point3D& other) {
		x = other.x; y = other.y; z = other.y;
		return this;
	}

	void randomize() {//temp for testing. Randomizes the values of the point.
		x = rand() % 100;
		y = rand() % 100;
		z = rand() % 100;
	}

private:

};

#endif
