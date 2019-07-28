#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
#include <conio.h>
#include "sstream"
#include "Bank.h"
#include "File.h"

const string DATA_BANK = "D:/TaLangBanking/Data/Bank/";
const string DATA_ACCOUNTCLIENT = "D:/TaLangBanking/Data/Client/Account/";
const string DATA_PROFILECLIENT = "D:/TaLangBanking/Data/Client/Profile/";

// Load Data
Date convertToDate(string x)
{
	int day, month, year;
	for (int i = 0; i < 2; i++)
	{
		auto work = x.find_first_of('/');
		string temp = x.substr(0, work);
		if (i == 0)
		{
			day = stoi(temp);
		}
		else
		{
			month = stoi(temp);
		}
		x.erase(x.begin(), x.begin() + work + 1);
	}
	year = stoi(x);
	return Date(day, month, year);
}
Client * loadDataClient(string UserID)
{
	// Load information of Cus
	string file_path = DATA_PROFILECLIENT + UserID + ".txt";
	string name = readline(file_path.c_str(), 1);
	name.erase(name.begin(), name.begin() + 6);
	string socialID = readline(file_path.c_str(), 2);
	socialID.erase(socialID.begin(), socialID.begin() + 10);
	string mail = readline(file_path.c_str(), 3);
	mail.erase(mail.begin(), mail.begin() + 6);
	string dob = readline(file_path.c_str(), 4);
	dob.erase(dob.begin(), dob.begin() + 5);
	Date day = convertToDate(dob);
	string addr = readline(file_path.c_str(), 5);
	addr.erase(addr.begin(), addr.begin() + 9);
	string sex = readline(file_path.c_str(), 6);
	sex.erase(sex.begin(), sex.begin() + 5);
	bool sexual = (sex.size() == 4);
	string salary = readline(file_path.c_str(), 7);
	salary.erase(salary.begin(), salary.begin() + 8);
	// Load Account Bank of Cus
	Client *cl = new Client(name, addr, socialID, UserID, mail, day, sexual, stof(salary));
	file_path = DATA_ACCOUNTCLIENT + UserID + ".txt";
	string amount = readline(file_path.c_str(), 1);
	vector <UserAccount*> bankAcc;
	for (int i = 0; i < stoi(amount); i++)
	{
		string work[3];
		string line = readline(file_path.c_str(), i + 3);
		for (int j = 0; j < 3; j++)
		{
			auto stop = line.find_first_of('|');
			work[j] = line.substr(0, stop);
			line.erase(line.begin(), line.begin() + stop + 1);
		}
		UserAccount *useracc = new UserAccount(work[0], work[1], work[0], stod(work[2]), stod(line), cl);
		bankAcc.push_back(useracc);
	}

	cl->setBankAccount(bankAcc);
	return cl;
}

void loadDataBank(vector <Bank*> &bank)
{
	for (int i = 0; i < 4; i++)
	{
		char temp = '0' + (i + 1);
		string file_path = DATA_BANK + "DataClient" + temp + ".txt";
		string addr = readline(file_path.c_str(), 2);
		addr.erase(addr.begin(), addr.begin() + 6);
		string president = readline(file_path.c_str(), 3);
		president.erase(president.begin(), president.begin() + 10);
		string phone = readline(file_path.c_str(), 4);
		phone.erase(phone.begin(), phone.begin() + 7);
		Bank *x = new Bank("TaLang iBanking", addr, president, phone);
		vector <Client*> cl;
		int j = 6;
		string UserID;
		while ((UserID = readline(file_path.c_str(), j)) != "This line doesn't exist\n")
		{
			if (j >= 6 && j <= 14)
			{
				UserID.erase(UserID.begin(), UserID.begin() + 2);
			}
			else
			{
				UserID.erase(UserID.begin(), UserID.begin() + 3);
			}
			Client *temp2 = loadDataClient(UserID); //Load Data for Customer
			cl.push_back(temp2);
			j++;
		}
		x->setCustomer(cl);
		bank.push_back(x);
	}
}

void loadDataBlackList()
{

}
// Save Data
void saveDataClient(Client *customer)
{
	// Save information of Customer
	string file_path;
	stringstream content1,content2;
	Date x = customer->getDob();
	content1 << "Name: " << customer->getName() << "\n";
	content1 << "SocialID: " << customer->getSocialID() << "\n";
	content1 << "Mail: " << customer->getEmail() << "\n";
	content1 << "DoB: " << x.getMDay() << "/" << x.getMMonth() << "/" << x.getMYear() << "\n";
	content1 << "Address: " << customer->getAddress() << "\n";
	content1 << "Sex: " << (customer->getSex() != 0 ? "Male" : "Female") << "\n";
	content1 << "Salary: " << to_string(long long(customer->getSalary()));
	file_path = DATA_PROFILECLIENT + customer->getUserID() + ".txt";
	write(file_path.c_str(), content1.str());
	// Save Account Bank of Customer
	file_path = DATA_ACCOUNTCLIENT + customer->getUserID() + ".txt";
	vector <UserAccount*> bankAccount;
	customer->setBankAccount(bankAccount);
	content2 << bankAccount.size() << "\n";
	content2 << "NumberID|password|balance|limit" << "\n";
	for (int i = 0; i < bankAccount.size(); i++)
	{
		content2 << bankAccount[i]->getNumID() << "|";
		content2 << bankAccount[i]->getPassword() << "|";
		content2 << to_string(long long (bankAccount[i]->getBalance())) << "|";
		content2 << to_string(long long (bankAccount[i]->getLimit())) << "\n";
	}
	write(file_path.c_str(), content2.str());
	customer->setBankAccount(bankAccount);
}
void saveDataBank(vector <Bank*> bank)
{
	vector <Client*> cus;
	for (int i = 0; i < bank.size(); i++)
	{
		bank[i]->setCustomer(cus);
		for (int j = 0; j < cus.size(); j++)
		{
			saveDataClient(cus[j]);
		}
		bank[i]->setCustomer(cus);
	}
}