#include <iostream>
#include "MYSQL_Income.h"
#include "MYSQL_Expense.h"
#include "DbFunction_Income.h"
#include "DbFunction_Expense.h"
#include "TotalFunction.h"

using namespace std;

int main() {
	DbFunction_Income DbIncome;
	DbFunction_Expense DbExpense;
	TotalFunction totalFunc;

	int n1, n2;
;
	DbIncome.inconnect();
	DbExpense.connect();
	totalFunc.inconnect();
	totalFunc.connect();
	DbIncome.show_Income();
	DbExpense.show_Expense();

	cout << "---���Ͻô� ����� �����ϼ���---" << endl;
	cout << "1. �Է��ϱ�\t\t" << "2. �����ϱ�" << endl << "3. �����ϱ�\t\t" << "4. �˻��ϱ�" << endl << "5. �м� ���� Ȯ��\t" << "6. ����" << "\n\n";
	cin >> n1;

	switch (n1) {
	case 1:
		cout << "1. ���Գ��� �Է��ϱ�\t\t" << "2. ���⳻�� �Է��ϱ�" << endl;
		cin >> n2;
		cout << endl;
		if (n2 == 1) {
			DbIncome.add_Income();
			break;
		}
		else if (n2 == 2) {
			DbExpense.add_Expense();
			break;
		}
		else {
			cout << "�˸��� ���ڸ� �Է��ϼ���." << endl;
			break;
		}
	case 2:
		cout << "1. ���Գ��� �����ϱ�\t\t" << "2. ���⳻�� �����ϱ�" << "\n\n";
		cin >> n2;
		if (n2 == 1) {
			DbIncome.delete_Income();
			break;
		}
		else if (n2 == 2) {
			DbExpense.delete_Expense();
			break;
		}
		else {
			cout << "�˸��� ���ڸ� �Է��ϼ���." << endl;
			break;
		}
	case 3:
		cout << "1. ���Գ��� �����ϱ�\t\t" << "2. ���⳻�� �����ϱ�" << "\n\n";
		cin >> n2;
		if (n2 == 1) {
			DbIncome.update_Income();
			break;
		}
		else if (n2 == 2) {
			DbExpense.update_Expense();
			break;
		}
		else {
			cout << "�˸��� ���ڸ� �Է��ϼ���." << endl;
			break;
		}
	case 4:
		cout << "1. �׸����� �˻��ϱ�\t\t" << "2. ��¥�� �˻��ϱ�" << "\n\n";
		cin >> n2;
		if (n2 == 1) {
			totalFunc.search_name();
			break;
		}
		else if (n2 == 2) {
			totalFunc.search_date();
			break;
		}
		else {
			cout << "�˸��� ���ڸ� �Է��ϼ���." << endl;
			break;
		}
	case 5:
		totalFunc.report();
		break;
	case 6:
		cout << "���α׷��� �����մϴ�." << endl;
		break;
	default:
		cout << "�˸��� ���ڸ� �Է��ϼ���." << endl;
		break;
	}

	return 0;
}