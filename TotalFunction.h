#pragma once
#include "MYSQL_Income.h"
#include "MYSQL_Expense.h"
#include "DbFunction_Income.h"
#include "DbFunction_Expense.h"

using namespace std;

class TotalFunction : public MySQL_Income, public MySQL_Expense {
public:
	void report();
	void search_name();
	void search_date();
};