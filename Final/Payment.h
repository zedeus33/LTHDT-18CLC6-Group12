#pragma once
#include "File.h"
#include "Function_Sup.h"
#define BILL_LINE 5

const string DATA_WATERBILL = "D:/TaLangBanking/Data/Payment/Water Bill/";
const string DATA_ELECTRICBILL = "D:/TaLangBanking/Data/Payment/Electric Bill/";

using namespace std;

class Payment
{
public:
	Payment();
	~Payment();
	virtual string paymentBill(UserAccount* &customer) = 0;
};


Payment::Payment()
{

}

Payment::~Payment()
{

}

string function_paymentsup(string file_path,string code, UserAccount *&customer)
{
	int max = 0;
	string temp, money, context[BILL_LINE];
	for (int i = 0; i < BILL_LINE; i++)
	{
		context[i] = readline(file_path.c_str(), i + 1);
		if (context[i] == "Can't open file\n")
		{
			return "THIS CODE DOESN'T EXIST";
		}
		if (context[i].size() > max)
		{
			max = context[i].size();
		}
	}
	temp = context[0];
	temp.erase(temp.begin(), temp.end() - 3);
	if (temp == "(1)")
	{
		return "BILL " + code + " HAS ALREADY PAYED";
	}
	for (int i = 0; i < max + 1; i++)
	{
		cout << "_";
	}
	cout << endl;
	for (int i = 0; i < BILL_LINE; i++)
	{
		cout << context[i] << setw(max + 1 - context[i].size()) << "|" << endl;
	}
	for (int i = 0; i < max + 1; i++)
	{
		if (i == max)
		{
			cout << "|\n";
		}
		else
		{
			cout << "_";
		}
	}
	string choice;
	cout << "Are you sure to payment(yes/no): ";
	cin >> choice;
	if (_stricmp(choice.c_str(), "yes") == 0)
	{
		money = context[3];
		money.erase(money.begin(), money.begin() + 27);
		money.erase(money.end() - 5, money.end());
		money = deleteChar(money, '.');
		if (customer->changeBalance(-stod(money)) == true)
		{
			context[0] = context[0] + "(1)\n" + context[1] + "\n" + context[2] + "\n" + context[3] + "\n" + context[4];
			write(file_path.c_str(), context[0]);
			return "PAYMENT SUCCESSFULLY";
		}
		else
		{
			return "YOUR BALANCE IS NOT ENOUGH MONEY";
		}
	}
	else if (_stricmp(choice.c_str(), "no") == 0)
	{
		return "return";
	}
	else
	{
		return "ERROR TYPE -.-";
	}
}
