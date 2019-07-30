#pragma once
#include "Client.h"

class Bank
{
public:
	Bank();
	Bank(string name, string address, string president_name, string phone_number);
	void show_infor();
	void addNewUser();
	Bank& operator=(Bank&x);
	string getAddress();
	string getName();
	string getPresident_name();
	string getPhone_number();
	void setAddress(string address);
	void setName(string name);
	void setPresident_name(string president_name);
	void setPhone_number(string phone_number);
	void setCustomer(vector <Client*> &temp);
	~Bank();

private:
	string name;
	string address;
	string president_name;
	string phone_number;
	vector <Client*> cus;
};
