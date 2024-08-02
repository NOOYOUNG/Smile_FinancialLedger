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

	cout << "---원하시는 기능을 선택하세요---" << endl;
	cout << "1. 입력하기\t\t" << "2. 삭제하기" << endl << "3. 수정하기\t\t" << "4. 검색하기" << endl << "5. 분석 보고서 확인\t" << "6. 종료" << "\n\n";
	cin >> n1;

	switch (n1) {
	case 1:
		cout << "1. 수입내역 입력하기\t\t" << "2. 지출내역 입력하기" << endl;
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
			cout << "알맞은 숫자를 입력하세요." << endl;
			break;
		}
	case 2:
		cout << "1. 수입내역 삭제하기\t\t" << "2. 지출내역 삭제하기" << "\n\n";
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
			cout << "알맞은 숫자를 입력하세요." << endl;
			break;
		}
	case 3:
		cout << "1. 수입내역 수정하기\t\t" << "2. 지출내역 수정하기" << "\n\n";
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
			cout << "알맞은 숫자를 입력하세요." << endl;
			break;
		}
	case 4:
		cout << "1. 항목으로 검색하기\t\t" << "2. 날짜로 검색하기" << "\n\n";
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
			cout << "알맞은 숫자를 입력하세요." << endl;
			break;
		}
	case 5:
		totalFunc.report();
		break;
	case 6:
		cout << "프로그램을 종료합니다." << endl;
		break;
	default:
		cout << "알맞은 숫자를 입력하세요." << endl;
		break;
	}

	return 0;
}