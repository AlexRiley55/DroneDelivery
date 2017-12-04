//#pragma once
#ifndef __ORDERDAO_H
#define __ORDERDAO_H

#include <iostream>
#include <vector>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "Order.h"

#include <stdlib.h>
#include <iostream>


class OrderDAO{
public:
	sql::Driver *driver;
	sql::Connection *con;

	OrderDAO();
	~OrderDAO();

	void CreateOrder(Order* o);

	int getOrderCount();

	std::vector<Order*> getOrders();
	
	Order* ReadOrder(int id);

	Order* UpdateOrder(int id, int newStatus);

	void DeleteOrder(int id);
	

};

#endif