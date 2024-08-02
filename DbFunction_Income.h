#pragma once
#include "MySQL_Income.h"

class DbFunction_Income : public MySQL_Income {
public:
	void show_Income();
	void add_Income();
	void delete_Income();
	void update_Income();
};