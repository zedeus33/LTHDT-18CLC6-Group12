#pragma once
#include "Payment.h"

const string DATA_ELECTRICBILL = "D:/TaLangBanking/Data/Payment/Electric Bill/";

class PaymentElectricBill : public Payment
{
public:
	PaymentElectricBill ();
	~PaymentElectricBill ();
	string paymentBill(UserAccount* &customer);
private:

};

PaymentElectricBill ::PaymentElectricBill ()
{

}

PaymentElectricBill ::~PaymentElectricBill ()
{

}

string PaymentElectricBill::paymentBill(UserAccount *& customer)
{
	int max = 0;
	string code,context[BILL_LINE];
	cout << "PLEASE ENTER BILL CODE: ";
	cin >> code;
	string file_path = DATA_ELECTRICBILL + code + ".txt";
	cout << endl;
	for (int i = 0; i < BILL_LINE; i++)
	{
		context[i] = readline(file_path.c_str(), i+1);
		if (context[i] == "Can't open file\n")
		{
			return "THIS BILL CODE DOESN'T EXIST";
		}
		if (context[i].size()>max)
		{
			max = context[i].size();
		}
	}
	for (int i = 0; i < max+1; i++)
	{
		cout << "_";
	}
	for (int i = 0; i < BILL_LINE; i++)
	{
		context[i] = readline(file_path.c_str(), i + 1);
		cout << context << setw(max + 1) << "|" << endl;
	}
	for (int i = 0; i < max+1; i++)
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
	if (_stricmp(choice.c_str(),"yes") == 0)
	{
		context[3].erase(context[3].begin(), context[3].begin() + 27);
		context[3].erase(context[3].end() + 5, context[3].end());
		context[3] = deleteChar(context[3], '.');
		if (customer->changeBalance(stod(context[3])) == true)
		{
			return "Payment successfully";
		}
		else
		{
			return "Your balance is not enough money";
		}
	}
	else
	{
		return "return";
	}
}
