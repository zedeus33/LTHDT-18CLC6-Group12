#pragma once
#include "Account.h"

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
	UserAccount(string u, string p, string n, double b, double l,Client* &Ref);
	UserAccount(const UserAccount &a);
	UserAccount& operator=(const UserAccount &a);
	void setClient(Client* a);
	string getNumID();
	double getBalance();
	double getLimit();
	string getLevel();
	Client* getRefClient();
	bool transfer(UserAccount *&numIDTransferTo, double value);
	/*string getPassword();*/
	void setPassword(string pass);
	void setUserName();
	bool changeBalance(double value);
	void Input();
	void Output();
	~UserAccount();

};