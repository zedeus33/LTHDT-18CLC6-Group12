#pragma once
#include "File.h"
#include "Bank.h"
#include <sstream>
#include <iomanip>
#define BILL_LINE 5
using namespace std;



class Payment
{
public:
	Payment();
	~Payment();
	virtual string paymentBill(UserAccount* &customer) = 0;
};

Payment::Payment()
{

}

Payment::~Payment()
{

}

string deleteChar(string content, char character)
{
	stringstream temp;
	for (int i = 0; i < content.size(); i++)
	{
		if (content[i] != character)
		{
			temp << content[i];
		}
	}
	return temp.str();
}