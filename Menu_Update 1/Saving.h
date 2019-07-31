#pragma once
#include "UserAccount.h"
class Saving
{
private:
	double S_balance;
	UserAccount* RefUserAccount;
	double Rate;
	double Period;
public:
	Saving();
	Saving(double money, int period, UserAccount *cur);
	Saving(double money, UserAccount* cur);
	Saving(double sbalance, UserAccount *a, double rate, double period);
	UserAccount* getRefUserAccount();
	void setUserAccount(UserAccount* a);
	void setSbalance(double s);
	double calcInterestAfterPeriod();
	double calcInterestPerMonth();
	double calcInterestNoPeriod(int day);
	double getSbalance();
	UserAccount* getRef();
	double getRate();
	double getPeriod();
	void output1();
	void output2();
};