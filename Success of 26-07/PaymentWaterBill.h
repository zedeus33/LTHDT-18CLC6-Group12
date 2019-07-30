#pragma once
#include "Payment.h"



class PaymentWaterBill : public Payment
{
public:
	PaymentWaterBill();
	~PaymentWaterBill();
	string paymentBill(UserAccount* &customer);
private:

};

PaymentWaterBill::PaymentWaterBill()
{

}

PaymentWaterBill::~PaymentWaterBill()
{
}

string PaymentWaterBill::paymentBill(UserAccount *& customer)
{
	string code;
	cout << "PLEASE ENTER BILL CODE: ";
	cin >> code;
	string file_path = DATA_WATERBILL + code + ".txt";
	return function_paymentsup(file_path,code, customer);
}
