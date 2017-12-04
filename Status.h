#ifndef __STATUS_H
#define __STATUS_H

class Status {
	enum StatusEnum {Initial, RouteReady, EnRoute, Complete, Failed, Archived};
	StatusEnum status;
};

#endif