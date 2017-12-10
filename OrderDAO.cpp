#include "stdafx.h"
#include "OrderDAO.h"
using namespace std;

OrderDAO::OrderDAO() {
	/* Create a connection */
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "tree");
	/* Connect to the MySQL test database */
	con->setSchema("delivery");

}


OrderDAO::~OrderDAO() {
		delete con;
}

void  OrderDAO::CreateOrder(Order* o) {
	sql::PreparedStatement *pstmt;
	//sql::ResultSet *res;
	
	pstmt = con->prepareStatement("INSERT INTO Orders (SrcX, SrcY, SrcZ, DestX, DestY, DestZ, StatusKey) VALUES(?, ?, ?, ?, ?, ?, ?)");

	pstmt->setInt(1, o->source.x);
	pstmt->setInt(2, o->source.y);
	pstmt->setInt(3, o->source.z);
	pstmt->setInt(4, o->dest.x);
	pstmt->setInt(5, o->dest.y);
	pstmt->setInt(6, o->dest.z);
	pstmt->setInt(7, o->StatusKey);

	int resInt = pstmt->executeUpdate();
	
	std::cout <<"Create Order result:" << resInt << std::endl;

	//delete res;
	delete pstmt;
	
}



int OrderDAO::getOrderCount() {
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * from Orders");
	int count = 0;
	while (res->next()) {
		count++;
	}
	std::cout << "Row count " << count << std::endl;
	delete res;
	delete stmt;
	return count;
}

std::vector<Order*> OrderDAO::getOrders(){
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM Orders o, Status s WHERE o.StatusKey = s.StatusID");

	delete stmt;

	std::vector<Order*> output;

	while (res->next()) {
		Point3D s;
		s.x = res->getInt(2);  s.y = res->getInt(3); s.z = res->getInt(4);
		Point3D d;
		d.x = res->getInt(5);  d.y = res->getInt(6); d.z = res->getInt(7);

		Order* out = new Order(res->getInt(1), s, d, res->getInt(8));

		output.push_back(out);
	}

	delete res;

	return output;
}

std::vector<Order*> OrderDAO::getInitialOrders() {
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM Orders o, Status s WHERE o.StatusKey = s.StatusID AND s.StatusDesc = \'Initial\'");

	delete stmt;

	std::vector<Order*> output;

	while (res->next()) {
		Point3D s;
		s.x = res->getInt(2);  s.y = res->getInt(3); s.z = res->getInt(4);
		Point3D d;
		d.x = res->getInt(5);  d.y = res->getInt(6); d.z = res->getInt(7);

		Order* out = new Order(res->getInt(1), s, d, res->getInt(8));

		output.push_back(out);
	}

	delete res;
	return output;
}


Order* OrderDAO::ReadOrder(int id) {
	con->setSchema("delivery");

	sql::Statement* stmt = con->createStatement();
	std::string query = "SELECT * FROM orders WHERE OrderID = " + id;
	sql::ResultSet* res = stmt->executeQuery(query);
	delete stmt;

	res->next();
	Point3D s;
	s.x = res->getInt(2);  s.y = res->getInt(3); s.z = res->getInt(4);
	Point3D d;
	d.x = res->getInt(5);  d.y = res->getInt(6); d.z = res->getInt(7);

	Order* out = new Order(res->getInt(1), s, d, res->getInt(8));
	delete res;
	return out;
}

Order* OrderDAO::updateOrder(int id, int newStatus) {//TODO: do this
	sql::PreparedStatement *pstmt;

	pstmt = con->prepareStatement("UPDATE Orders SET StatusKey = ? WHERE OrderID = ?)");

	pstmt->setInt(1, newStatus);
	pstmt->setInt(2, id);

	int resInt = pstmt->executeUpdate();

	std::cout << "Create Order result:" << resInt << std::endl;

	delete pstmt;

	Order* out = new Order();//TODO do this
	return out;
}

void OrderDAO::DeleteOrder(int id) {//TODO: do this

}

