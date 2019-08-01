#include "Admin.h"
#include <algorithm>
#include "BlackList.h"
#include "Behaviors.h"
#include <fstream>
using namespace std;
string readline2(const char* path, int line);


Admin::Admin(string acc, string pw)
{
	this->username = acc;
	this->password = pw;
}

Admin::~Admin()
{
}

bool Admin::createUser(Client*& p, string numID)
{	
	UserAccount* lamda = new UserAccount("","",numID,0,0,p);
	vector<UserAccount*> rha = p->getBackAccount();
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

bool Admin::unBlockUser(UserAccount*& rha)
{
	BlackList* p = BlackList::getBlackList();
	bool addblock = p->removeFromBlackList(rha->getNumID());
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

UserAccount* Admin::searchUserAccount(vector<Bank*> glo, string numID)
{
	for (auto& bank : glo)
	{
		for (auto& client : bank->getClient())
		{
			UserAccount* rha = client->findAccount(numID);
			if (rha != nullptr)
				return rha;
		}
	}
	return nullptr;
}


void Admin::viewRequestLog(vector<Bank*> glo)
{
	vector <string> UserID;
	vector <string> numID;
	if (LoadRequireNewUserAccount(UserID, numID))
	{
		vector<string>::iterator i = UserID.begin();
		vector<string>::iterator j = numID.begin();
		int t = 1;
		for (i, j; i != UserID.end(); i++, j++)
		{
			Client* p = this->searchUser(glo, *i);
			cout << t++ << ". " << p->getUserID() << "|" << *j << endl;
			bool is_good = this->createUser(p, *j);
			if (is_good)
			{
				cout << "This request have been excuted successfully" << endl;
			}
		}
	}
	else
		cout << "There is no request :>" << endl;
	
}

void saveRequireNewUserAccount(Client*& customer)
{
	string file_path = "./RequireNewAccount.txt";
	string context = customer->getUserID() + "|" + createDefaultNumID() + "\n";
	Behaviors* p = new LoginBehavior();
	p->saveLog(context.c_str(),file_path.c_str());
}

bool LoadRequireNewUserAccount(vector <string>& UserID, vector <string>& numID) // If have require return true else return false
{
	string file_path = "./RequireNewAccount.txt";
	ifstream fin(file_path);
	if (!fin.is_open())
		return false;
	fin.close();
	string temp;
	int i = 1;
	do
	{
		temp = readline2(file_path.c_str(), i);
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
	return true;
}

string readline2(const char* path, int line)
{
	ifstream fin;
	fin.open(path);
	if (fin.is_open() == true)
	{
		int i = 1;
		string temp;
		while (fin.eof() == false)
		{
			getline(fin, temp, '\n');
			if (temp == "")
			{
				continue;
			}
			if (line == i)
			{
				fin.close();
				return temp;
			}
			i++;
		}
		fin.close();
		return "This line doesn't exist\n";
	}
	else
	{
		return "Can't open file\n";
	}
}