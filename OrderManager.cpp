#include "stdafx.h"
#include "OrderManager.h"

OrderManager::OrderManager(){
	DAO = new OrderDAO();
	fileName = "orders.csv";
}

OrderManager::OrderManager(std::string fn){
	DAO = new OrderDAO();
	fileName = fn;
}

OrderManager::~OrderManager(){
}

void OrderManager::ReadOrdersFromFile(std::string file){
	std::string line;
	std::ifstream orderFile(file);

	if (orderFile.is_open()){
		
		std::getline(orderFile, line);//first line is the labels

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

std::vector<Order*> OrderManager::getOrders(){
	return DAO->getOrders();
}

void OrderManager::CreateOrder(Order* o){
	DAO->CreateOrder(o);
}

std::vector<Order*> OrderManager::ReadOrders(std::string s){
	return std::vector<Order*>();//TODO:do this
}

void OrderManager::run(){
	ReadOrdersFromFile(fileName);
}

void OrderManager::writeDatabase(std::string file) {//TODO go grab the actual status
	std::ofstream outputFile(file);
	if (outputFile.is_open()) {
		outputFile << "OrderID,";
		outputFile << "SrcX,";
		outputFile << "SrcY,";
		outputFile << "SrcZ,";
		outputFile << "DestX,";
		outputFile << "DestY,";
		outputFile << "DestZ,";
		outputFile << "StatusKey,";
		outputFile << "\n";

		std::vector<Order*> temp = getOrders();
		for (int i = 0; i < temp.size(); i++) {
			outputFile << temp[i]->ID;
			outputFile << ",";
			outputFile << temp[i]->source.x;
			outputFile << ",";
			outputFile << temp[i]->source.y;
			outputFile << ",";
			outputFile << temp[i]->source.z;
			outputFile << ",";
			outputFile << temp[i]->dest.x;
			outputFile << ",";
			outputFile << temp[i]->dest.y;
			outputFile << ",";
			outputFile << temp[i]->dest.z;
			outputFile << ",";
			outputFile << temp[i]->StatusKey;
			outputFile << "\n";
		}

		outputFile.close();
	}
}
