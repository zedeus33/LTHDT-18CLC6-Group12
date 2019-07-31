#pragma once
#include "Account.h"

#include <vector>

class Client;
class Saving;
class UserAccount : public Account
{
private:
	string numID;
	double Balance;
	double limit;
	Client* RefClient;
	vector <Saving*> list;
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
	bool transfer(UserAccount *&to, double value);
	/*string getPassword();*/
	void setPassword(string pass);
	void setUserName();
	bool changeBalance(double value);
	void changeToSaving(double money);
	void Input();
	void Output();
	bool CreateSavingPeriod(double money, int period);
	bool CreateSavingNoPeriod(double money);
	int getListsize();
	void outputList();
	~UserAccount();

};