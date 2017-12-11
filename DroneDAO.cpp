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
	sql::Statement *IDpstmt;
	sql::ResultSet *res;
	pstmt = con->prepareStatement("INSERT INTO Drones (DroneStatusKey) VALUES(?)");
	//pstmt->setInt(1, d->order.ID);//TODO add a version to upload a full drone
	//pstmt->setInt(2, d->route.ID);
	pstmt->setInt(1, d->Status);

	int resInt = pstmt->executeUpdate();
	//TODO stored procedure to fill other tables if they don't exist.

	IDpstmt = con->createStatement();
	res = IDpstmt->executeQuery("SELECT LAST_INSERT_ID() AS id;"); //TODO: is this thread safe?
	delete pstmt;

	res->next();
	int id = res->getInt("id");
	delete IDpstmt;
	delete res;

	sql::PreparedStatement *dbpstmt;

	dbpstmt = con->prepareStatement("INSERT INTO DroneDirtyBit (DroneKey, DirtyBit) VALUES(?, ?)");
	dbpstmt->setInt(1, id);
	dbpstmt->setInt(2, 1);

	int resInt2 = dbpstmt->executeUpdate();

	std::cout << "Update Dirty Bit result:" << resInt2 << std::endl;

	delete dbpstmt;

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

Drone * DroneDAO::UpdateRoute(Drone* d){
	sql::PreparedStatement *pstmt;

	pstmt = con->prepareStatement("UPDATE Drones SET OrderKey = ?, RoutesKey = ?, DroneStatusKey = ? WHERE DroneID = ?");

	pstmt->setInt(1, d->route.OrderKey);
	pstmt->setInt(2, d->route.ID);
	pstmt->setInt(3, d->Status);
	pstmt->setInt(4, d->ID);

	int resInt = pstmt->executeUpdate();

	std::cout << "Create Order result:" << resInt << std::endl;

	delete pstmt;

	return nullptr;//TODO
}

void DroneDAO::CleanDirtyBit(int ID) {
	sql::PreparedStatement *dbpstmt;

	dbpstmt = con->prepareStatement("UPDATE DroneDirtyBit SET DirtyBit = 0 WHERE DroneKey = ?");
	dbpstmt->setInt(1, ID);

	int resInt = dbpstmt->executeUpdate();

	std::cout << "Update DirtyBit result:" << resInt << std::endl;

	delete dbpstmt;
}

Drone * DroneDAO::UpdateRoute(int id, int status) {
	sql::PreparedStatement *pstmt;

	pstmt = con->prepareStatement("UPDATE Drones StatusKey = ? WHERE OrderID = ?");

	pstmt->setInt(1, status);
	pstmt->setInt(2, id);

	int resInt = pstmt->executeUpdate();

	std::cout << "Create Order result:" << resInt << std::endl;

	delete pstmt;

	return nullptr;//TODO
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

std::vector<Drone*> DroneDAO::getDirtyDrones() {//only grabs the 4 ints, the DM assembles the rest
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM Drones d, DroneDirtyBit db WHERE d.DroneID = db.DroneKey AND db.DirtyBit = 1;");
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

std::vector<Drone*> DroneDAO::getDronesByStatus(int status) {//only grabs the 4 ints, the DM assembles the rest
	sql::PreparedStatement *pstmt;
	sql::ResultSet *res;
	pstmt = con->prepareStatement("SELECT * FROM Drones WHERE DroneStatusKey = ?");
	pstmt->setInt(1, status);
	res = pstmt->executeQuery();
	delete pstmt;

	std::vector<Drone*> output;

	while (res->next()) {
		int id = res->getInt(1);
		int ok = res->getInt(2);
		int rk = res->getInt(3);

		Drone* out = new Drone(id, ok, rk, status);
		output.push_back(out);
	}

	delete res;
	return output;
}

std::vector<Drone*> DroneDAO::getDirtyDronesByStatus(int status) {//only grabs the 4 ints, the DM assembles the rest
	sql::PreparedStatement *pstmt;
	sql::ResultSet *res;
	pstmt = con->prepareStatement("SELECT * FROM Drones d, DroneDirtyBit db WHERE d.DroneID = db.DroneKey AND db.DirtyBit = 1 AND DroneStatusKey = ?");
	pstmt->setInt(1, status);
	res = pstmt->executeQuery();
	delete pstmt;

	std::vector<Drone*> output;

	while (res->next()) {
		int id = res->getInt(1);
		int ok = res->getInt(2);
		int rk = res->getInt(3);

		Drone* out = new Drone(id, ok, rk, status);
		output.push_back(out);
	}

	delete res;
	return output;
}
