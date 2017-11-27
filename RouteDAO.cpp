#include "stdafx.h"
#include "RouteDAO.h"
using namespace std;

RouteDAO::RouteDAO() {
	
	/* Create a connection */
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "tree");
	/* Connect to the MySQL test database */
	con->setSchema("delivery");

}


RouteDAO::~RouteDAO() {
		delete con;
}

Route*  RouteDAO::CreateRoute(Route* r) {
	sql::PreparedStatement *pstmt;
	sql::Statement *PKStmt;
	sql::ResultSet *res;
	
	pstmt = con->prepareStatement("INSERT INTO Routes (OrderKey) VALUES(?)");
	pstmt->setInt(1, r->OrderKey);
	
	int resInt = pstmt->executeUpdate();

	PKStmt = con->createStatement();

	res = PKStmt->executeQuery("SELECT LAST_INSERT_ID() AS id;"); //TODO: is this thread safe?

	res->next();
	int PK = res->getInt("id");

	r->ID = PK;

	for(int i = 1; i < r->Routes.size() -1; i++){
		CreatePoint(PK, i, r->Routes[i]);
	}

	delete res;
	delete pstmt;
	return r;
	
}

void RouteDAO::CreatePoint(int routeID, int pointNum, Point3D p)
{
	sql::PreparedStatement *pstmt;
	//sql::ResultSet *res;

	pstmt = con->prepareStatement("INSERT INTO RoutePosition (RoutesKey, PositionNum, x, y, z) VALUES(?, ?, ?, ?, ?)");
	pstmt->setInt(1, routeID);
	pstmt->setInt(2, pointNum);
	pstmt->setInt(3, p.x);
	pstmt->setInt(4, p.y);
	pstmt->setInt(5, p.z);

	int resInt = pstmt->executeUpdate();
	std::cout << "Create Point result:" << resInt << std::endl; //TODO: is this right?

	//delete res;
	delete pstmt;
}


int RouteDAO::getRouteCount() {
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();//TODO: use prepared statement
	res = stmt->executeQuery("SELECT * FROM Routes");
	int count = 0;
	while (res->next()) {
		count++;
	}
	std::cout << "Row count " << count << std::endl;
	delete res;
	delete stmt;
	return count;
}


Route* RouteDAO::ReadRoute(int id) {//TODO: unfinished
	con->setSchema("delivery");

	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	std::string query = "SELECT * FROM Routes r,RoutePosition rp WHERE RouteID = " + id;
	query += " AND r.RouteID = rp.RoutesKey";
	res = stmt->executeQuery(query);
	while (res->next()) {
		cout << res->getString("_message") << endl;
		cout << res->getString(1) << endl;
	}
	

	Route* out = new Route();
	return out;
}

Route* RouteDAO::UpdateRoute(int id, int newStatus) {//TODO: unfinished
	Route* out = new Route();
	return out;
}

void RouteDAO::DeleteRoute(int id) {//TODO: unfinished

}

