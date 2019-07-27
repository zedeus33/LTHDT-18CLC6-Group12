#pragma once
#include <vector>
#include <iomanip>
#include "UserAccount.h"
#include "Date.h"
#include <string>
#include <cstring>
#include <sstream>

#define MAX_ACCOUNT 10

class Client
{
private:
	string name;
	string address;
	string SocialID;
	string UserID;
	string Email;
	vector <UserAccount*> BankAccount;
	int numOfAccount;
	Date DoB;	
	bool Sex;
	double Salary;
//	Bank* bank;
public:
	Client();
	//~Client();
	void input();
	void output();
	bool OpenNewAccount();
	bool CloseAccount();
	//bool Deposit(float value);
	//bool WithDraw(float value);
	bool operator ==(const Client *& a);
	string createPassword();
	string createUserName();
	void display();
	UserAccount* findAccount(string numID);
	bool changeBalance(string numID, double value);
};
