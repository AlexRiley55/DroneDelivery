#include "stdafx.h"
#include "DroneDAO.h"


DroneDAO::DroneDAO(){
	/* Create a connection */
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "tree");
	/* Connect to the MySQL test database */
	con->setSchema("delivery");
}


DroneDAO::~DroneDAO(){
	delete con;
}

Drone * DroneDAO::CreateDrone(Drone * d){
	sql::PreparedStatement *pstmt;

	pstmt = con->prepareStatement("INSERT INTO Drones (DroneStatusKey) VALUES(?)");
	//pstmt->setInt(1, d->order.ID);//TODO add a version to upload a full drone
	//pstmt->setInt(2, d->route.ID);
	pstmt->setInt(1, d->Status);

	int resInt = pstmt->executeUpdate();
	delete pstmt;
	//TODO stored procedure to fill other tables if they don't exist.

	return nullptr;//TODO return the drone back
}

int DroneDAO::getDroneCount(){
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();//TODO: use prepared statement
	res = stmt->executeQuery("SELECT * FROM Drones");
	delete stmt;

	int count = 0;
	while (res->next()) {
		count++;
	}
	std::cout << "Drone count " << count << std::endl;
	delete res;
	return count;
}

Drone * DroneDAO::ReadRoute(int id){
	con->setSchema("delivery");

	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	std::string query = "SELECT * FROM Drones d,DroneStatus ds WHERE DroneStatusID = DroneStatusKey AND DroneID = " + id;//TODO I don't think this actually works, should be tested.
	query += " AND r.RouteID = rp.RoutesKey";
	res = stmt->executeQuery(query);
	delete stmt;

	while (res->next()) {
		std::cout << res->getString("_message") << std::endl;
		std::cout << res->getString(1) << std::endl;
	}

	delete res;
	Drone* out = new Drone();//TODO either do this or remove for final version
	return out;
}

Drone * DroneDAO::UpdateRoute(int id, int newStatus){//TODO
	return nullptr;
}

void DroneDAO::DeleteRoute(int id){//TODO

}

std::vector<Drone*> DroneDAO::getDrones(){//only grabs the 4 ints, the DM assembles the rest
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM Drones");
	delete stmt;

	std::vector<Drone*> output;

	while (res->next()) {
		int id = res->getInt(1);
		int ok = res->getInt(2);
		int rk = res->getInt(3);
		int s = res->getInt(4);

		Drone* out = new Drone(id, ok, rk, s);
		output.push_back(out);
	}

	delete res;
	return output;
}
