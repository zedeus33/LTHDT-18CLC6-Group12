#pragma once
#include "Account.h"
class Client;
class UserAccount : public Account
{
private:
	string numID;
	double Balance;
	double limit;
	Client *RefClient;
public:
	UserAccount();
	UserAccount(string n, double b, double l);
	UserAccount(string u, string p, string n, double b, double l,Client* &Ref);
	UserAccount(const UserAccount &a);
	UserAccount& operator=(const UserAccount &a);
	Client* getRef();
	string getNumID();
	double getBalance();
	double getLimit();
	string getLevel();
	void Input();
	void Output();
	void setPassword(string pass);
	bool transfer(UserAccount *&numIDTransferTo,double value);
	~UserAccount();

};