#include "UserAccount.h"
#include "Client.h"
#include "Account.h"
#include "Behaviors.h"
#include "Saving.h"
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

	if (value > Balance || value > limit || value < 0)
	{
		return false;
	}
	else
	{
		Behaviors* p;
		do
		{
			p = new TransferBehavior(value);
			p->sentOTP(this->getRefClient()->getEmail());
			if (checkOTP(p) == true)
			{
				p->saveLog(p->toString().c_str(), bh_mkdir(this).c_str());
				to->Balance = to->Balance + value;
				this->Balance = this->Balance - value;
				return true;
			}
			else
			{
				notice("Wrong OTP,please try again", ".", ".");
			}
		} while (checkOTP(p)==false);
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

void UserAccount::changeToSaving(double money)
{
	Balance = Balance - money;
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

bool UserAccount::CreateSavingPeriod(double money, int period)
{
	if (list.size() >= 1)
	{
		cout << "You can not create more saving book" << endl;
		return false;
	}
	else if(money>=(Balance-50000)){

		cout << "Your balance is not enought money to open new Saving book!" << endl;
		return false;
	}
	else
	{
		Saving* a = new Saving(money, period, this);
		Balance = Balance - money;
		cout << "Your accrued interest after period is : " << a->calcInterestAfterPeriod() << endl;
		list.push_back(a);
		return true;
	}
}

bool UserAccount::CreateSavingNoPeriod(double money)
{
	if (list.size() >= 1) {
		cout << "You can not create more saving book!" << endl;
		return false;
	}
	else if(money>=(Balance-50000)){
		cout << "Your balance is not enought to open new Saving book!" << endl;
		return false;
	}
	else
	{
		Saving* a = new Saving(money, this);
		Balance = Balance - money;
		cout << "Your interest per month is : " << a->calcInterestPerMonth() << endl;
		list.push_back(a);
		return true;
	}
}

int UserAccount::getListsize()
{
	return list.size();
}

void UserAccount::setListSaving(vector<Saving*>& list)
{
	this->list.swap(list);
}

void UserAccount::outputList()
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << "Saving book 1 :" << endl;
		if (list[i]->getRate() == 0.01)
		{
			list[i]->output1();
		}
		else if (list[i]->getRate() == 0.005)
		{
			list[i]->output2();
		}
	}
}

UserAccount::~UserAccount()
{
	numID = "";
	Balance = 50000;
	limit = 0;
}

