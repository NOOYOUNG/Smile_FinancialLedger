#include <iostream>
using namespace std;

#include "MYSQL_Expense.h"

MySQL_Expense::MySQL_Expense() {
	
}

MySQL_Expense::~MySQL_Expense() {
	mysql_close(&expense);
}

void MySQL_Expense::connect() {
	mysql_init(&expense);

	if (!mysql_real_connect(&expense, "localhost", "root", "root", "ledger", 3306, NULL, 0)) {
		cerr << "Failed to connect Mysql" << mysql_error(&expense) << endl;
	}

	mysql_query(&expense, "set session character_set_connection=euckr;");
	mysql_query(&expense, "set session character_set_results=euckr;");
	mysql_query(&expense, "set session character_set_client=euckr;");
}