#pragma once
#ifndef Client_h
#define Client_h
#include <vector>
#include <sstream>
#include <iomanip>
#include "UserAccount.h"
#include "Date.h"
#include "Function_Sup.h"

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
	void setBankAccount(vector <UserAccount*> &x) 
	{
		this->numOfAccount = x.size();
		this->BankAccount.swap(x);
	}
	Client(string name, string addr, string SocialID, string UserID, string email, Date dob, bool sex, float salary);
	void input();
	void output();
	bool OpenNewAccount();
	bool CloseAccount();
	bool operator ==(const Client *& a);
	string createPassword();
	string getName();
	string getUserID();
	UserAccount* findAccount(string numID);
};
#endif // !Client_h
