#include "UserAccount.h"

UserAccount::UserAccount() : Account()
{
	numID = "";
	Balance = 50000;
	limit = 10000000;
}

UserAccount::UserAccount(string n, double b, double l) : Account()
{
	numID = n;
	Balance = 50000 + b;
	limit = 10000000 + l;

}

UserAccount::UserAccount(string u, string p, string n, double b, double l) : Account(u, p)
{
	numID = n;
	Balance = 50000 + b;
	limit = 10000000 + l;
}

UserAccount::UserAccount(const UserAccount & a)
{
	Account::operator=(a);
	numID = a.numID;
	Balance = a.Balance;
	limit = a.limit;
}

UserAccount & UserAccount::operator=(const UserAccount & a)
{
	Account::operator=(a);
	numID = a.numID;
	Balance = a.Balance;
	limit = a.limit;
	return *this;
}

string UserAccount::getNumID()
{
	return numID;
}

double UserAccount::getBalance()
{
	return Balance;
}

double UserAccount::getLimit()
{
	return limit;
}

string UserAccount::getLevel()
{
	if (limit < 50000000)
	{
		return "Silver";
	}
	else if (limit < 100000000)
	{
		return "Gold";
	}
	else return "Platinum";
}

void UserAccount::Input()
{
	Account::Input();
	cout << "Enter number ID : ";
	getline(cin, numID);
	cout << "Enter balance : ";
	cin >> Balance;
	Balance += 50000;
	cout << "Enter limit : ";
	cin >> limit;
	limit += 10000000;
}

void UserAccount::Output()
{
	Account::Output();
	cout << "Num ID : " << numID << endl;
	cout << "Balance : " << Balance << endl;
	cout << "Limit : " << limit << endl;
	cout << "Level : " << this->getLevel() << endl;
}

UserAccount::~UserAccount()
{
	numID = "";
	Balance = 50000;
	limit = 0;
}