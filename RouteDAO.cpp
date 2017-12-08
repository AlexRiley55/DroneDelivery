#include "stdafx.h"
#include "RouteDAO.h"

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
	delete pstmt;

	PKStmt = con->createStatement();

	res = PKStmt->executeQuery("SELECT LAST_INSERT_ID() AS id;"); //TODO: is this thread safe?
	delete PKStmt;

	res->next();
	int PK = res->getInt("id");

	r->ID = PK;

	for(int i = 1; i < r->Routes.size() -1; i++){
		CreatePoint(PK, i, r->Routes[i]);
	}

	delete res;
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
	delete pstmt;

	std::cout << "Create Point result:" << resInt << std::endl; //TODO: is this right?

}


int RouteDAO::getRouteCount() {
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();//TODO: use prepared statement
	res = stmt->executeQuery("SELECT * FROM Routes");
	delete stmt;

	int count = 0;
	while (res->next()) {
		count++;
	}
	std::cout << "Row count " << count << std::endl;
	delete res;
	return count;
}


Route* RouteDAO::ReadRoute(int id) {//TODO: unfinished
	con->setSchema("delivery");

	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	std::string query = "SELECT * FROM Routes r,RoutePosition rp WHERE RouteID = " + id;//TODO I don't think this actually works, should be tested.
	query += " AND r.RouteID = rp.RoutesKey";
	res = stmt->executeQuery(query);
	delete stmt;

	while (res->next()) {
		std::cout << res->getString("_message") << std::endl;
		std::cout << res->getString(1) << std::endl;
	}
	
	delete res;
	Route* out = new Route();//TODO either do this or remove for final version
	return out;
}

Route* RouteDAO::UpdateRoute(int id, int newStatus) {//TODO: unfinished
	Route* out = new Route();
	return out;
}

void RouteDAO::DeleteRoute(int id) {//TODO: unfinished

}

std::vector<Route*> RouteDAO::getRoutes(){
	sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM Routes");
	delete stmt;

	std::vector<Route*> output;

	while (res->next()) {
		int ok = res->getInt(2);
		int id = res->getInt(1);
		std::vector<Point3D> vec = getPoints(id);
		Route* out = new Route(ok, id, vec);
		output.push_back(out);
	}

	delete res;
	return output;
}

std::vector<Point3D> RouteDAO::getPoints(int id) {
	/*sql::Statement *stmt;
	sql::ResultSet *res;
	stmt = con->createStatement();
	std::string str = "SELECT * RoutePosition rp WHERE rp.RoutesKey = " + id;
	str + ";";
	res = stmt->executeQuery(str);

	delete stmt;*/

	sql::PreparedStatement *pstmt;
	sql::ResultSet *res;

	pstmt = con->prepareStatement("SELECT * FROM RoutePosition WHERE RoutesKey = ?;");
	pstmt->setInt(1, id);

	res = pstmt->executeQuery();
	delete pstmt;

	std::vector<Point3D> output;

	while (res->next()) {
		Point3D p;

		p.x = res->getInt(3);
		p.y = res->getInt(4);
		p.z = res->getInt(5);
		
		output.push_back(p);
	}
	
	delete res;
	return output;
}

