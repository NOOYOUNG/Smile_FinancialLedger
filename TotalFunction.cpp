#include "TotalFunction.h"
#include <iostream>
#include <string>
#include <mysql.h>
#include <time.h>

using namespace std;

void TotalFunction::report() {
	int month, last_month;
	cout << "분석할 달의 숫자를 입력하세요: ";

	while (true) {
		cin >> month;
		if (month >= 1 && month <= 12) {
			break;
		}
		else {
			cout << "알맞은 숫자를 입력하세요: ";
		}
	}

	last_month = (month == 1) ? 12 : month - 1;

	cout << "\n\n***" << month << "월의 종합 보고서***" << endl;

	string select_income = "SELECT SUM(price) FROM income WHERE MONTH(date)=" + to_string(month);
	string select_expense = "SELECT SUM(price) FROM expense WHERE MONTH(date)=" + to_string(month);

	if (mysql_query(&income, select_income.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	if (mysql_query(&expense, select_expense.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	MYSQL_RES* sInResult = mysql_store_result(&income);
	MYSQL_RES* sExResult = mysql_store_result(&expense);

	if (!sInResult || !sExResult) {
		cerr << "Failed to retrieve result\n" << mysql_error(&income) << endl << mysql_error(&expense) << endl;
	}

	//보고서 내용 작성
	MYSQL_ROW income_Row = mysql_fetch_row(sInResult);
	string totalIncome = (income_Row[0] ? income_Row[0] : "0");
	cout << "이번달 수입 총액은 (+)" << totalIncome << "원입니다." << endl; //NULL값인지 확인

	MYSQL_ROW expense_Row = mysql_fetch_row(sExResult);
	string totalExpense = (expense_Row[0] ? expense_Row[0] : "0");
	cout << "이번달 지출 총액은 (-)" << totalExpense << "원입니다." << endl;

	string last_income = "SELECT SUM(price) FROM income WHERE MONTH(date)=" + to_string(last_month);
	string last_expense = "SELECT SUM(price) FROM expense WHERE MONTH(date)=" + to_string(last_month);

	if (mysql_query(&income, last_income.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	if (mysql_query(&expense, last_expense.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	MYSQL_RES* lastInResult = mysql_store_result(&income);
	MYSQL_RES* lastExResult = mysql_store_result(&expense);

	if (!lastInResult || !lastExResult) {
		cerr << "Failed to retrieve result\n" << mysql_error(&income) << endl << mysql_error(&expense) << endl;
	}

	MYSQL_ROW lastInRow = mysql_fetch_row(lastInResult);
	string last_totalIncome = (lastInRow[0] ? lastInRow[0] : "0");
	cout << "지난달 수입 총액은 (+)" << last_totalIncome << "원입니다." << endl;

	MYSQL_ROW lastExRow = mysql_fetch_row(lastExResult);
	string last_totalExpense = (lastExRow[0] ? lastExRow[0] : "0");
	cout << "지난달 지출 총액은 (-)" << last_totalExpense << "원입니다." << endl;

	int income_diff = stoi(totalIncome) - stoi(last_totalIncome);
	double in_per = 0;
	if (income_diff < 0) {
		in_per = (stod(last_totalIncome) - stod(totalIncome)) / stod(last_totalIncome) * 100;
		cout << "\n지난달에 비해 수익이 " << abs(income_diff) << "원(-" << in_per << "%) 감소하였습니다.\n";
	}
	else if (income_diff == 0) {
		cout << "\n지난달과 수익이 동일합니다.\n";
	}
	else {
		in_per = (stod(totalIncome) - stod(last_totalIncome)) / stod(last_totalIncome) * 100;
		cout << "\n지난달에 비해 수익이 " << income_diff << "원(+" << in_per << "%) 증가하였습니다.\n";
	}

	int expense_diff = stoi(totalExpense) - stoi(last_totalExpense);
	double ex_per = 0;
	if (expense_diff < 0) {
		ex_per = (stod(last_totalExpense) - stod(totalExpense)) / stod(last_totalExpense) * 100;
		cout << "\n지난달에 비해 지출이 " << abs(expense_diff) << "원(-" << ex_per << "%) 감소하였습니다.\n";
	}
	else if (expense_diff == 0) {
		cout << "\n지난달과 지출이 동일합니다.\n";
	}
	else {
		ex_per = (stod(totalExpense) - stod(last_totalExpense)) / stod(last_totalExpense) * 100;
		cout << "\n지난달에 비해 지출이 " << expense_diff << "원(+" << ex_per << "%) 증가하였습니다.\n";
	}

	mysql_free_result(sInResult);
	mysql_free_result(sExResult);
	mysql_free_result(lastInResult);
	mysql_free_result(lastExResult);

	cout << "***보고서 마침***\n\n\n";
}

void TotalFunction::search_name() {
	string sName;
	cout << "검색할 항목을 입력하세요: ";
	cin >> sName;
	cout << endl;

	string select_income = "SELECT name, price, date, id FROM income WHERE name='" + sName + "'";
	string select_expense = "SELECT name, price, date, id FROM expense WHERE name='" + sName + "'";

	if (mysql_query(&income, select_income.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	if (mysql_query(&expense, select_expense.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	MYSQL_RES* sInResult = mysql_store_result(&income);
	MYSQL_RES* sExResult = mysql_store_result(&expense);

	if (!sInResult || !sExResult) {
		cerr << "Failed to retrieve result\n" << mysql_error(&income) << endl << mysql_error(&expense) << endl;
	}

	int i_fields = mysql_num_fields(sInResult);
	int e_fields = mysql_num_fields(sExResult);
	cout << "[수입내역 검색]\n";
	while ((in_Row = mysql_fetch_row(sInResult))) {
		for (int i = 0; i < i_fields - 1; i++) {
			cout << (in_Row[i] ? in_Row[i] : "NULL") << " ";
		}
		cout << "  (" << in_Row[i_fields - 1] << ")";
		cout << endl;
	}
	cout << "\n[지출내역 검색]\n";
	while ((ex_Row = mysql_fetch_row(sExResult))) {
		for (int i = 0; i < e_fields - 1; i++) {
			cout << (ex_Row[i] ? ex_Row[i] : "NULL") << " ";
		}
		cout << "  (" << ex_Row[e_fields - 1] << ")";
		cout << endl;
	}

	mysql_free_result(sInResult);
	mysql_free_result(sExResult);

	cout << "\n\n";
}

void TotalFunction::search_date() {
	string sDate;
	cout << "검색할 날짜를 입력하세요 (YYYY-MM-DD): ";
	cin >> sDate;
	cout << endl;

	string select_income = "SELECT name, price, date FROM income WHERE date='" + sDate + "'";
	string select_expense = "SELECT name, price, date FROM expense WHERE date='" + sDate + "'";

	if (mysql_query(&income, select_income.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&income) << endl;
	}

	if (mysql_query(&expense, select_expense.c_str())) {
		cerr << "Query Execution Error" << mysql_error(&expense) << endl;
	}

	MYSQL_RES* sInResult = mysql_store_result(&income);
	MYSQL_RES* sExResult = mysql_store_result(&expense);

	if (!sInResult || !sExResult) {
		cerr << "Failed to retrieve result\n" << mysql_error(&income) << endl << mysql_error(&expense) << endl;
	}

	int i_fields = mysql_num_fields(sInResult);
	int e_fields = mysql_num_fields(sExResult);
	cout << "[수입내역 검색]\n";
	while ((in_Row = mysql_fetch_row(sInResult))) {
		for (int i = 0; i < i_fields - 1; i++) {
			cout << (in_Row[i] ? in_Row[i] : "NULL") << " ";
		}
		cout << "  (" << in_Row[i_fields - 1] << ")";
		cout << endl;
	}
	cout << "\n[지출내역 검색]\n";
	while ((ex_Row = mysql_fetch_row(sExResult))) {
		for (int i = 0; i < e_fields - 1; i++) {
			cout << (ex_Row[i] ? ex_Row[i] : "NULL") << " ";
		}
		cout << "  (" << ex_Row[e_fields - 1] << ")";
		cout << endl;
	}

	mysql_free_result(sInResult);
	mysql_free_result(sExResult);

	cout << "\n\n";
}