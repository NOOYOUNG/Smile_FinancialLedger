#pragma once
#include <mysql.h>

class MySQL_Expense {
public:
	MySQL_Expense();
	~MySQL_Expense();
	void connect();
protected:
	MYSQL expense;
	MYSQL_RES* ex_Result = NULL;
	MYSQL_ROW ex_Row = NULL;
};