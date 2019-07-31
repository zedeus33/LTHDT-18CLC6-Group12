#include "Saving.h"

Saving::Saving()
{
	S_balance = 0;
	RefUserAccount = NULL;
	Rate = 0;
	Period = 0;
}

Saving::Saving(double money, int period, UserAccount *cur)
{
	S_balance = money;
	RefUserAccount = cur;
	Period = double(period);
	Rate = 0.01;

}

Saving::Saving(double money, UserAccount* cur)
{
	S_balance = money;
	RefUserAccount = cur;
	Rate = 0.005;
	Period = 0;
}

Saving::Saving(double sbalance, UserAccount* a, double rate, double period)
{
	S_balance = sbalance;
	RefUserAccount = a;
	Rate = rate;
	Period = period;
}

Saving::Saving(double sbalance, double rate, double period)
{
	this->S_balance = sbalance;
	this->Rate = rate;
	this->Period = period;
}

UserAccount* Saving::getRefUserAccount()
{
	return RefUserAccount;
}

void Saving::setUserAccount(UserAccount* a)
{
	RefUserAccount = a;
}

void Saving::setSbalance(double s)
{
	S_balance = s;
}

double Saving::calcInterestAfterPeriod()
{
	return ((S_balance * Rate * Period) / 12);
}

double Saving::calcInterestPerMonth()
{
	return ((S_balance * Rate) / 12);
}

double Saving::calcInterestNoPeriod(int day)
{
	return S_balance*(Rate/12)*double(day);
}

double Saving::getSbalance()
{
	return S_balance;
}

UserAccount* Saving::getRef()
{
	return RefUserAccount;
}

double Saving::getRate()
{
	return Rate;
}

double Saving::getPeriod()
{
	return Period;
}

void Saving::output1()
{
	cout << "\tYour saving's current type is : With Period" << endl;
	cout << "\tYour deposits : " << S_balance << endl;
	cout << "\tInterest After period : " << calcInterestAfterPeriod() << endl;
}

void Saving::output2()
{
	cout << "\tYour saving's current type is : Without Period" << endl;
	cout << "\tYour deposits : " << S_balance << endl;
	cout << "\tInterest per month : " << calcInterestPerMonth() << endl;
}
