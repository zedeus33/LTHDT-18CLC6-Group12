#pragma once
#include "Payment.h"



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
	string code;
	cout << "PLEASE ENTER BILL CODE: ";
	cin >> code;
	string file_path = DATA_ELECTRICBILL + code + ".txt";
	return function_paymentsup(file_path,code, customer);
}
