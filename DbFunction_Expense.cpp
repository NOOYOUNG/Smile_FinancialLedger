#include "DbFunction_Expense.h"
#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

void DbFunction_Expense::show_Expense() {
	cout << "지출내역" << endl;

	string select_expense = "SELECT name, price, date, id FROM expense ORDER BY date ASC, name ASC";

	if (mysql_query(&expense, select_expense.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	ex_Result = mysql_store_result(&expense);
	if (!ex_Result) {
		cerr << "Failed to retrieve result" << mysql_error(&expense) << endl;
	}

	int ex_fields = mysql_num_fields(ex_Result);
	while ((ex_Row = mysql_fetch_row(ex_Result))) {
		cout << "> ";
		for (int i = 0; i < ex_fields - 1; i++) {
			cout << (ex_Row[i] ? ex_Row[i] : "NULL") << " ";
		}
		cout << "  (" << ex_Row[ex_fields - 1] << ")";
		cout << endl;
	}

	mysql_free_result(ex_Result);
	cout << endl;
}

void DbFunction_Expense::add_Expense() {
	cout << "지출내역을 입력하세요." << endl;

	string name, date;
	int price;

	cout << "항목: ";
	cin >> name;
	cout << "금액: ";
	cin >> price;
	cout << "날짜 (YYYY-MM-DD): ";
	cin >> date;

	string insert_query
		= "INSERT INTO expense (name, price, date) VALUES ('" + name + "', " + to_string(price) + ", '" + date + "')";

	if (mysql_query(&expense, insert_query.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	cout << "정상적으로 입력되었습니다.\n\n";
}

void DbFunction_Expense::delete_Expense() {
	int id;
	cout << "삭제할 지출내역의 번호를 입력하세요: ";
	cin >> id;

	string delete_query
		= "DELETE FROM expense WHERE name='" + to_string(id) + "'";

	if (mysql_query(&expense, delete_query.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	cout << "내역이 정상적으로 삭제되었습니다.\n\n";
}

void DbFunction_Expense::update_Expense() {
	int id, price;
	string name, date;
	cout << "수정할 수입내역의 번호를 입력하세요: ";
	cin >> id;
	cout << "수정할 수입내역의 항목을 입력하세요:";
	cin >> name;
	cout << "수정할 수입내역의 가격을 입력하세요:";
	cin >> price;
	cout << "수정할 수입내역의 날짜를 입력하세요 (YYYY-MM-DD):";
	cin >> date;

	string update_query
		= "UPDATE expense SET name='" + name + "', price=" + to_string(price) + ", date='" + date + "' WHERE id=" + to_string(id);

	if (mysql_query(&expense, update_query.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	cout << "수정이 완료되었습니다.\n\n";
}