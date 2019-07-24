#pragma once
#ifndef Client_h
#define Client_h
#include <vector>
#include <sstream>
#include <iomanip>
#include "UserAccount.h"
#include "Date.h"
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
	bool Sex; // (0:female,1:male)
	float Salary;
	
//	Bank*
public:
	Client();
	//~Client();
	void input();
	void output();
	bool OpenNewAccount();
	bool CloseAccount();
	//bool Deposit(float value);
	//bool WithDraw(float value);
	//bool Transfer(float value, string AccountID);
	bool operator ==(const Client *& a);
	string createPassword();
	string createUserName();
	
};
#endif // !Client_h