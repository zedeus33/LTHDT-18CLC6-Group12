#include "Account.h"

Account::Account()
{
	username = "";
	password = "";
}

Account::Account(string u, string p)
{
	username = u;
	password = p;
}

Account::Account(const Account & a)
{
	username = a.username;
	password = a.password;
}

Account & Account::operator=(const Account & a)
{
	username = a.username;
	password = a.password;
	return *this;
}

string Account::getUsername()
{
	return username;
}

string Account::getPassword()
{
	return password;
}

void Account::Encrypt()
{

}

bool Account::Authetication(string u, string p)
{
	if (username == u && password == p)
	{
		return true;
	}
	else return false;
}

void Account::Input()
{
	if (cin.get() != '\n')
		cin.ignore();
	cout << "Enter username : ";
	getline(cin, username);
	cout << "Enter password : ";
	getline(cin, password);
}

void Account::Output()
{
	cout << "Username : " << username << endl;
	cout << "Password : " << password << endl;
}

Account::~Account()
{
	username = "";
	password = "";
}
