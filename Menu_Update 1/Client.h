#ifndef Client_h
#define Client_h
#include <vector>
#include <sstream>
#include <iomanip>
#include "UserAccount.h"
#include "Date.h"
#include "Function_Sup.h"

#define MAX_ACCOUNT 10

class Client
{
private:
	string name;
	string address;
	string SocialID;
	string UserID;
	string Email;
	vector <UserAccount*> BankAccount;
	int numOfAccount;
	Date DoB;
	bool Sex; // (0:female,1:male)
	float Salary;

	//	Bank*
public:
	Client();
	void setBankAccount(vector <UserAccount*> &x) 
	{
		this->numOfAccount = x.size();
		this->BankAccount.swap(x);
	}
	Client(string name, string addr, string SocialID, string UserID, string email, Date dob, bool sex, float salary);	
	Client(const Client& rha);
	void input();
	void input2(UserAccount *a);
	void inputDoB();
	void output();
	bool OpenNewAccount();
	bool CloseAccount();
	//bool Deposit(float value);
	//bool WithDraw(float value);
	//bool Transfer(float value, string AccountID);
	void createDefaultUserAccount();
	bool operator ==(const Client *& a);
	string getUserID()
	{
		return UserID;
	}
	string createPassword();
	string getName();
	//string createUserName();
	void display();
	UserAccount* findAccount(string numID);
	int changeBalance(string numID, double value);
	string getEmail();
	Date getDob();
	bool getSex();
	float getSalary();
	string getAddress();
	string getSocialID();
};
#endif // !Client_h