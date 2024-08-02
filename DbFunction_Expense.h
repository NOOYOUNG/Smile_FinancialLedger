#pragma once
#include "MySQL_Expense.h"

class DbFunction_Expense : public MySQL_Expense {
public:
	void show_Expense();
	void add_Expense();
	void delete_Expense();
	void update_Expense();
};