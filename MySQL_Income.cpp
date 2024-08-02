#include <iostream>
using namespace std;

#include "MYSQL_Income.h"

MySQL_Income::MySQL_Income() {
	
}

MySQL_Income::~MySQL_Income() {
	mysql_close(&income);
}

void MySQL_Income::inconnect() {
	mysql_init(&income);
	if (!mysql_real_connect(&income, "localhost", "root", "root", "ledger", 3306, NULL, 0)) {
		cerr << "Failed to connect Mysql" << mysql_error(&income) << endl;
	}

	mysql_query(&income, "set session character_set_connection=euckr;");
	mysql_query(&income, "set session character_set_results=euckr;");
	mysql_query(&income, "set session character_set_client=euckr;");
}