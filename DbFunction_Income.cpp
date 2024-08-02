#include "DbFunction_Income.h"
#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

void DbFunction_Income::show_Income() {
	cout << "���Գ���" << endl;

	string select_income = "SELECT name, price, date, id FROM income ORDER BY date ASC, name ASC";

	if (mysql_query(&income, select_income.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	in_Result = mysql_store_result(&income);
	if (!in_Result) {
		cerr << "Failed to retrieve result" << mysql_error(&income) << endl;
	}

	int in_fields = mysql_num_fields(in_Result);
	while ((in_Row = mysql_fetch_row(in_Result))) {
		cout << "> ";
		for (int i = 0; i < in_fields - 1; i++) {
			cout << (in_Row[i] ? in_Row[i] : "NULL") << " ";
		}
		cout << "  (" << in_Row[in_fields - 1] << ")";
		cout << endl;
	}

	mysql_free_result(in_Result);
	cout << endl;
}

void DbFunction_Income::add_Income() {
	string name, date;
	int price;

	cout << "�׸�: ";
	cin >> name;
	cout << "�ݾ�: ";
	cin >> price;
	cout << "��¥ (YYYY-MM-DD): ";
	cin >> date;

	string insert_query
		= "INSERT INTO income (name, price, date) VALUES ('" + name + "', " + to_string(price) + ", '" + date + "')";

	if (mysql_query(&income, insert_query.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	cout << "���������� �ԷµǾ����ϴ�.\n\n";
}

void DbFunction_Income::delete_Income() {
	int id;
	cout << "������ ���Գ����� ��ȣ�� �Է��ϼ���: ";
	cin >> id;

	string delete_query
		= "DELETE FROM income WHERE id='" + to_string(id) + "'";

	if (mysql_query(&income, delete_query.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	cout << "������ ���������� �����Ǿ����ϴ�.\n\n";
}

void DbFunction_Income::update_Income() {
	int id, price;
	string name, date;
	cout << "������ ���Գ����� ��ȣ�� �Է��ϼ���: ";
	cin >> id;
	cout << "������ ���Գ����� �׸��� �Է��ϼ���:";
	cin >> name;
	cout << "������ ���Գ����� ������ �Է��ϼ���:";
	cin >> price;
	cout << "������ ���Գ����� ��¥�� �Է��ϼ��� (YYYY-MM-DD):";
	cin >> date;

	string update_query
		= "UPDATE income SET name='" + name + "', price=" + to_string(price) + ", date='" + date + "' WHERE id=" + to_string(id);

	if (mysql_query(&income, update_query.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	cout << "������ �Ϸ�Ǿ����ϴ�.\n\n";
}