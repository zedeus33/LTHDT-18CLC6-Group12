#include "UserAccount.h"
#include "Client.h"
#include "Account.h"
#include "Behaviors.h"

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

UserAccount::UserAccount(string u, string p, string n, double b, double l,Client *&Ref) : Account(u, p)
{
	numID = n;
	Balance = 50000 + b;
	limit = 10000000 + l;
	RefClient = Ref;
}

UserAccount::UserAccount(const UserAccount & a)
{
	Account::operator=(a);
	numID = a.numID;
	Balance = a.Balance;
	limit = a.limit;
	
}

UserAccount & UserAccount::operator=(const UserAccount &a)
{
	Account::operator=(a);
	numID = a.numID;
	Balance = a.Balance;
	limit = a.limit;
	return *this;
}

void UserAccount::setClient(Client* a)
{
	RefClient = a;
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

Client* UserAccount::getRefClient()
{
	return this->RefClient;
}

bool UserAccount::transfer(UserAccount *& to, double value)
{

	if (value > Balance || value > limit)
	{
		return false;
	}
	else
	{
		Behaviors* p = new TransferBehavior(value);
		p->sentOTP(this->getRefClient()->getEmail());
		if (checkOTP(p) == true)
		{
			p->saveLog(p->toString().c_str(), bh_mkdir(this).c_str());
			to->Balance = to->Balance + value;
			this->Balance = this->Balance - value;
			return true;
		}
	}
}

//string UserAccount::getPassword()
//{
//	return Account::getPassword();
//}

void UserAccount::setPassword(string pass)
{
	password = pass;
}

void UserAccount::setUserName()
{
	username = numID;
}

bool UserAccount::changeBalance(double value)
{
	if (-value > Balance)
	{
		return 0;
	}
	else
	{
		Balance += value;
		return 1;
	}
}

void UserAccount::Input()
{
	//Account::Input();
	cout << "Enter number ID : ";
	getline(cin, numID);
	cout << "Enter balance : ";
	cin >> Balance;
	Balance += 50000;
	cout << "Enter limit : ";
	cin >> limit;
	limit += 10000000;
	//password = RefClient->createPassword();
	//username = ();
}

void UserAccount::Output()
{
	Account::Output();
	cout << "Name : " << RefClient->getName() << endl;
	cout << "Email : " << RefClient->getEmail() << endl;
	cout << "Num ID : " << numID << endl;
	cout << "Balance : " << fixed << setprecision(2) << Balance << endl;
	cout << "Limit : " << fixed << setprecision(2) << limit << endl;
	cout << "Level : " << this->getLevel() << endl;
}



UserAccount::~UserAccount()
{
	numID = "";
	Balance = 50000;
	limit = 0;
}

