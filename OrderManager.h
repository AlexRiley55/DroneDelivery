#ifndef __ORDERMANAGER_H
#define __ORDERMANAGER_H

#include "Manager.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Order.h"
#include "OrderDAO.h"
#include <vector>

class OrderManager : public Manager{
private:
	
public:
	OrderManager();
	OrderManager(std::string fn);
	~OrderManager();

	void ReadOrdersFromFile(std::string file); 

	void CreateOrder(Order* o);
	Order* ReadOrder(int id);
	std::vector<Order*> ReadOrders(std::string s);
	void run();

	std::vector<Order*> getOrders();
	std::vector<Order*> getInitialOrders();
	void updateOrder(int id, int status);

	void writeDatabase(std::string file);

	OrderDAO* DAO;
	std::string fileName;
};

#endif // !__ORDERMANAGER_H
