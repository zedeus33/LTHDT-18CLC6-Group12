#pragma once
#include "UserAccount.h"
class Saving : public UserAccount
{
private:
	double S_balance;
	UserAccount* RefUserAccount;
	double Rate;
	double Period;
public:
	Saving(double sbalance, UserAccount *a, double rate, double period);
	UserAccount* getRefUserAccount();
	void setUserAccount(UserAccount* a);
	void setSbalance(double s);
	double calcInterestAfterPeriod();
	double calcInterestPerMonth();
	double calcInterestNoPeriod(int day);
};