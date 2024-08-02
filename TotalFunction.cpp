#include "TotalFunction.h"
#include <iostream>
#include <string>
#include <mysql.h>
#include <time.h>

using namespace std;

void TotalFunction::report() {
	int month, last_month;
	cout << "�м��� ���� ���ڸ� �Է��ϼ���: ";

	while (true) {
		cin >> month;
		if (month >= 1 && month <= 12) {
			break;
		}
		else {
			cout << "�˸��� ���ڸ� �Է��ϼ���: ";
		}
	}

	last_month = (month == 1) ? 12 : month - 1;

	cout << "\n\n***" << month << "���� ���� ����***" << endl;

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

	//���� ���� �ۼ�
	MYSQL_ROW income_Row = mysql_fetch_row(sInResult);
	string totalIncome = (income_Row[0] ? income_Row[0] : "0");
	cout << "�̹��� ���� �Ѿ��� (+)" << totalIncome << "���Դϴ�." << endl; //NULL������ Ȯ��

	MYSQL_ROW expense_Row = mysql_fetch_row(sExResult);
	string totalExpense = (expense_Row[0] ? expense_Row[0] : "0");
	cout << "�̹��� ���� �Ѿ��� (-)" << totalExpense << "���Դϴ�." << endl;

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
	cout << "������ ���� �Ѿ��� (+)" << last_totalIncome << "���Դϴ�." << endl;

	MYSQL_ROW lastExRow = mysql_fetch_row(lastExResult);
	string last_totalExpense = (lastExRow[0] ? lastExRow[0] : "0");
	cout << "������ ���� �Ѿ��� (-)" << last_totalExpense << "���Դϴ�." << endl;

	int income_diff = stoi(totalIncome) - stoi(last_totalIncome);
	double in_per = 0;
	if (income_diff < 0) {
		in_per = (stod(last_totalIncome) - stod(totalIncome)) / stod(last_totalIncome) * 100;
		cout << "\n�����޿� ���� ������ " << abs(income_diff) << "��(-" << in_per << "%) �����Ͽ����ϴ�.\n";
	}
	else if (income_diff == 0) {
		cout << "\n�����ް� ������ �����մϴ�.\n";
	}
	else {
		in_per = (stod(totalIncome) - stod(last_totalIncome)) / stod(last_totalIncome) * 100;
		cout << "\n�����޿� ���� ������ " << income_diff << "��(+" << in_per << "%) �����Ͽ����ϴ�.\n";
	}

	int expense_diff = stoi(totalExpense) - stoi(last_totalExpense);
	double ex_per = 0;
	if (expense_diff < 0) {
		ex_per = (stod(last_totalExpense) - stod(totalExpense)) / stod(last_totalExpense) * 100;
		cout << "\n�����޿� ���� ������ " << abs(expense_diff) << "��(-" << ex_per << "%) �����Ͽ����ϴ�.\n";
	}
	else if (expense_diff == 0) {
		cout << "\n�����ް� ������ �����մϴ�.\n";
	}
	else {
		ex_per = (stod(totalExpense) - stod(last_totalExpense)) / stod(last_totalExpense) * 100;
		cout << "\n�����޿� ���� ������ " << expense_diff << "��(+" << ex_per << "%) �����Ͽ����ϴ�.\n";
	}

	mysql_free_result(sInResult);
	mysql_free_result(sExResult);
	mysql_free_result(lastInResult);
	mysql_free_result(lastExResult);

	cout << "***���� ��ħ***\n\n\n";
}

void TotalFunction::search_name() {
	string sName;
	cout << "�˻��� �׸��� �Է��ϼ���: ";
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
	cout << "[���Գ��� �˻�]\n";
	while ((in_Row = mysql_fetch_row(sInResult))) {
		for (int i = 0; i < i_fields - 1; i++) {
			cout << (in_Row[i] ? in_Row[i] : "NULL") << " ";
		}
		cout << "  (" << in_Row[i_fields - 1] << ")";
		cout << endl;
	}
	cout << "\n[���⳻�� �˻�]\n";
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
	cout << "�˻��� ��¥�� �Է��ϼ��� (YYYY-MM-DD): ";
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
	cout << "[���Գ��� �˻�]\n";
	while ((in_Row = mysql_fetch_row(sInResult))) {
		for (int i = 0; i < i_fields - 1; i++) {
			cout << (in_Row[i] ? in_Row[i] : "NULL") << " ";
		}
		cout << "  (" << in_Row[i_fields - 1] << ")";
		cout << endl;
	}
	cout << "\n[���⳻�� �˻�]\n";
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