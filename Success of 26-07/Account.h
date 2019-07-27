#ifndef Account_h
#define Account_h
#include <iostream>
#include <string>
using namespace std;
class Account
{
protected:
	string username;
	string password;
public:
	Account();
	Account(string u, string p);
	Account(const Account &a);
	Account& operator=(const Account &a);
	string getUsername();
	string getPassword();
	virtual void Encrypt();
	virtual bool Authetication(string u, string p);
	virtual void Input();
	virtual void Output();
	~Account();
};
#endif // !Account_h#pragma once
