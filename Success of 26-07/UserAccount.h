#pragma once
#include "Account.h"

class Client;
class UserAccount : public Account
{
private:
	string numID;
	double Balance;
	double limit;
	Client* RefClient;
public:
	UserAccount();
	UserAccount(string n, double b, double l);
	UserAccount(string u, string p, string n, double b, double l);
	UserAccount(const UserAccount &a);
	UserAccount& operator=(const UserAccount &a);
	void setClient(Client* a);
	string getNumID();
	double getBalance();
	double getLimit();
	string getLevel();
	bool changeBalance(double value);
	void Input();
	void Output();
	~UserAccount();

};