#pragma once
#include "UserAccount.h"
#include "Client.h"
#include "Blacklist.h" 
#include <vector>
#include <string>
class Bank;
using namespace std;
class Admin : public Account
{
	Bank* workBank;
	string name;
	string address;
	string userID;
public:
	explicit Admin(string acc,string pw);
	~Admin();
	bool createUser(vector<UserAccount*> &rha,Client *&p,string numID);
	bool blockUser(UserAccount *&rha);
	Client* searchUser(vector<Bank*> glo,string numID);
	void viewRequestLog(vector<Bank*> glo);
	void viewUserHistoryLog(UserAccount *&p);
	bool comfirmRequest(Client*& rha);
};

void saveRequireNewUserAccount(Client *&customer);
bool LoadRequireNewUserAccount(vector <string> &UserID, vector <string> &numID); // If have require return true else return false