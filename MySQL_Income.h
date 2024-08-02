#pragma once
#include <mysql.h>

class MySQL_Income {
public:
	MySQL_Income();
	~MySQL_Income();
	void inconnect();
protected:
	MYSQL income;
	MYSQL_RES* in_Result = NULL;
	MYSQL_ROW in_Row = NULL;
};