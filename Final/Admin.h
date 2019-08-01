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
	bool createUser(Client *&p,string numID);
	bool blockUser(UserAccount *&rha);
	bool unBlockUser(UserAccount*& rha);

	Client* searchUser(vector<Bank*> glo,string numID);
	void viewRequestLog(vector<Bank*> glo);
	void viewBlockRequestLog(vector<Bank*> glo);
	void viewUserHistoryLog(UserAccount *&p);
	bool comfirmRequest(Client*& rha);
	UserAccount* searchUserAccount(vector<Bank*> glo, string numID);
};

void saveRequireNewUserAccount(Client *&customer);
void saveRequiredBlockUserAccount(Client*& customer, UserAccount*& usacc);
bool LoadRequireNewUserAccount(vector <string> &UserID, vector <string> &numID); // If have require return true else return false
bool loadRequiredBlockUserAccount(vector<string>& UserID, vector<string>& numID);
