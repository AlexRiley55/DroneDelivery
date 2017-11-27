#ifndef __ORDERMANAGER_H
#define __ORDERMANAGER_H

#include "Manager.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Order.h"
#include "OrderDAO.h"

class OrderManager : public Manager{
public:
	OrderManager();
	~OrderManager();

	void ReadOrdersFromFile(std::string file);

	void CreateOrder(Order* o);
	std::vector<Order*> ReadOrders(std::string s);
	void run();

	std::vector<Order*> getInitalOrders();

	OrderDAO* DAO;
};

#endif // !__ORDERMANAGER_H
