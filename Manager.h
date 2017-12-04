#ifndef __MANAGER_H
#define __MANAGER_H

#include <string>

class Manager{

public:
	virtual void run() = 0;
	virtual void writeDatabase(std::string file) = 0;
private:

};

#endif // !__MANAGER_H

