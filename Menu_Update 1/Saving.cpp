#include "Saving.h"

Saving::Saving(double sbalance, UserAccount* a, double rate, double period)
{
	S_balance = sbalance;
	RefUserAccount = a;
	Rate = rate;
	Period = period;
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
	return ((S_balance * Rate * Period) / 365);
}

double Saving::calcInterestPerMonth()
{
	return ((S_balance * Rate) / 12);
}

double Saving::calcInterestNoPeriod(int day)
{
	return S_balance*(Rate/360)*double(day);
}
