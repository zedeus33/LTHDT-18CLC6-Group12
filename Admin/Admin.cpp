#include "Admin.h"
#include <algorithm>
#include "BlackList.h"
#include "Behaviors.h"
#include "Function_Sup.h"
#include "Function_Sup.cpp"
using namespace std;



Admin::Admin(string acc, string pw)
{
	this->username = acc;
	this->password = pw;
}

Admin::~Admin()
{
}

bool Admin::createUser(vector<UserAccount*>& rha,Client*& p, string numID)
{	
	UserAccount* lamda = new UserAccount("","",numID,0,0,p);
	if (binary_search(rha.begin(), rha.end(), lamda))
	{
		return false;
	}
	if (rha.size() < 10)
	{
		rha.push_back(lamda);
		return true;
	}
	else
		return false;
}
bool Admin::blockUser(UserAccount*& rha)
{
	BlackList* p = BlackList::getBlackList();
	bool addblock =	p->addToBlaskList(rha->getNumID());
	return addblock;
}

Client* Admin::searchUser(vector<Bank*> glo, string numID)
{
	for (auto& bank : glo)
	{
		for (auto& client : bank->getClient())
		{
			if (client->getUserID() == numID)
				return client;
		}
	}
	return nullptr;
}

void Admin::viewUserHistoryLog(UserAccount*& p)
{
	vector <Behaviors*> customer_behaviors;
	customer_behaviors = ReadData(p);
	for (auto& i : customer_behaviors)
	{
		cout << i->toScreen() << endl;
	}
}

bool Admin::comfirmRequest(Client*& rha)
{
	return false;
}


void Admin::viewRequestLog(vector<Bank*> glo)
{
	vector <string> UserID;
	vector <string> numID;
	LoadRequireNewUserAccount(UserID, numID);
	vector<string>::iterator i = UserID.begin();
	vector<string>::iterator j = numID.begin();
	for (i,j;i != UserID.end();i++,j++)
	{
		Client*p = this->searchUser(glo,*j);
		cout << p->getUserID();
	}
}

void saveRequireNewUserAccount(Client*& customer)
{
	string file_path = "./RequireNewAccount.txt";
	string context = customer->getUserID() + "|" + createDefaultNumID();
	addFile(file_path.c_str(), context, "\n");
}

bool LoadRequireNewUserAccount(vector <string>& UserID, vector <string>& numID) // If have require return true else return false
{
	string file_path = "./RequireNewAccount.txt";
	bool ans = checkFileExist(file_path.c_str());
	if (ans == false)
	{
		return ans;
	}
	string temp;
	int i = 1;
	do
	{
		temp = readline(file_path.c_str(), i);
		if (temp == "" || temp == "This line doesn't exist\n")
		{
			break;
		}
		auto pos = temp.find_first_of('|');
		UserID.push_back(temp.substr(0, pos));
		temp.erase(temp.begin(), temp.begin() + pos + 1);
		numID.push_back(temp);
		i++;
	} while (true);
	remove(file_path.c_str());
	return ans;
}
