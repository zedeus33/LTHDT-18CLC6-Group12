#include "Bank.h"

Bank::Bank()
{
	name = address = president_name = phone_number = "Default";
}

Bank::Bank(string name, string address, string president_name, string phone_number)
{
	this->name = name;
	this->address = address;
	this->president_name = president_name;
	this->phone_number = phone_number;
}

void Bank::show_infor()
{
	cout << "\t\t\t\t\t================\n";
	cout << "\t\t\t\t\tBank Information\n";
	cout << "\t\t\t\t\t================\n";
	cout << setw(16) << "Name: " << name << "\n";
	cout << setw(16) << "Address: " << address << "\n";
	cout << "President Name: " << president_name << "\n";
	cout << setw(16) << "Phone number: " << phone_number << "\n";
}

void Bank::addNewUser()
{
	Client *x = new Client;
	x->input();
	x->createDefaultUserAccount();
	for (int i = 0; i < this->cus.size(); i++)
	{
		if (x == cus[i])
		{
			notice("This account has already existed!!!", "=", "=");
			return;
		}
	}
	cus.push_back(x);
	cout << "Create successfully\n";
}


Bank & Bank::operator=(Bank & x)
{
	if (this == &x)
	{
		return *this;
	}
	this->name = x.name;
	this->address = x.address;
	this->president_name = x.president_name;
	this->phone_number = x.phone_number;
	this->cus.swap(x.cus);
	return *this;
}

string Bank::getAddress()
{
	return address;
}

string Bank::getName()
{
	return name;
}

void Bank::setAddress(string address)
{
	this->address = address;
}

void Bank::setName(string name)
{
	this->name = name;
}

void Bank::setPresident_name(string president_name)
{
	this->president_name = president_name;
}

void Bank::setPhone_number(string phone_number)
{
	this->phone_number = phone_number;
}

void Bank::setCustomer(vector<Client*> & temp)
{
	this->cus.swap(temp);
}

Bank::~Bank()
{
	name = address = president_name = phone_number = "";
}