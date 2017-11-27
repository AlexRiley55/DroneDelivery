#include "stdafx.h"
#include "OrderManager.h"

OrderManager::OrderManager(){
	DAO = new OrderDAO();
}

OrderManager::~OrderManager(){
}

void OrderManager::ReadOrdersFromFile(std::string file){
	std::string line;
	std::ifstream orderFile(file);

	if (orderFile.is_open()){
		
		while (std::getline(orderFile, line)){//TODO: Error checking
			std::stringstream ss(line);
			std::string temp;

			Order* out;

			int SrcX;
			int SrcY;
			int SrcZ;

			int DestX;
			int DestY;
			int DestZ;

			int Status;//TODO make this use the enum

			std::getline(ss, temp, ',');
			SrcX = stoi(temp);

			std::getline(ss, temp, ',');
			SrcY = stoi(temp);

			std::getline(ss, temp, ',');
			SrcZ = stoi(temp);

			std::getline(ss, temp, ',');
			DestX = stoi(temp);

			std::getline(ss, temp, ',');
			DestY = stoi(temp);

			std::getline(ss, temp, ',');
			DestZ = stoi(temp);

			Point3D s;
			s.x = SrcX;
			s.y = SrcY;
			s.z = SrcZ;

			Point3D d;
			d.x = DestX;
			d.y = DestY;
			d.z = DestZ;

			if(std::getline(ss, temp, ',')) {
				Status = stoi(temp);
				out = new Order(s, d, Status);
			} else {
				out = new Order(s, d);
			}

			CreateOrder(out);

		}
		
		orderFile.close();
	}

	else std::cout << "Unable to open file";
}

std::vector<Order*> OrderManager::getInitalOrders(){
	return DAO->getInitalOrders();
}

void OrderManager::CreateOrder(Order* o){
	DAO->CreateOrder(o);
}

std::vector<Order*> OrderManager::ReadOrders(std::string s){
	return std::vector<Order*>();//TODO:do this
}

void OrderManager::run(){
	ReadOrdersFromFile("Orders.txt");
}
