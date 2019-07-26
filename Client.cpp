#include "Client.h"
#include "Function.h"


Client::Client()
{
	name = "";
	address = "";
	numOfAccount = 0;
	SocialID = "";
	UserID = "";
	Email = "";
	Sex = 0;
	Salary = 0;
}

void Client::input()
{
	cout << "Enter name: ";
	getline(cin,name,'\n');
	cout << "Enter Address: ";
	getline(cin, address, '\n');
	Sex = InputBool(Sex, "Sex (0:Male,1:Female):");
	DoB.input();
	cin.ignore();
	Salary = InputDouble(Salary, "Enter Salary: ");
	cout << "Enter Social ID: ";
	cin.ignore();
	getline(cin, SocialID, '\n');
	cout << "Enter User ID: ";
	getline(cin,UserID,'\n');
	cout << "Enter Email: ";
	getline(cin, Email, '\n');
	
}

void Client::output()
{
	cout << "Name: " << name << endl;
	cout << "Address: " << address << endl;
	cout << "Social ID: " << SocialID << endl;
	cout << "User ID: " << UserID << endl;
	cout << "Email: " << Email << endl;
	cout << "Day of Birth: " << DoB.output()<< endl;
	cout << "Sex: ";
	if (Sex == 1)
	{
		cout << "Female" << endl;
	}
	else
	{
		cout << "Male" << endl;
	}
	cout << "Salary: " << Salary << endl;
	cout << "Number of account: " << numOfAccount << endl;
	for (int i = 0; i < BankAccount.size(); i++)
	{
		BankAccount[i]->Output();
	}
}

bool Client::OpenNewAccount()
{
	if (numOfAccount == MAX_ACCOUNT)
	{
		cout << "You already have the maximum number of account allowed!" << endl;
		cout << "You can not create more" << endl;
		cout << endl;
		return 0;
	}
	else
	{
		UserAccount * _new = new UserAccount;
		_new->Input();
		BankAccount.push_back(_new);
		numOfAccount++;
		cout << "Successfull" << endl;
		return 1;
	}
}

bool Client::CloseAccount()
{
	if (numOfAccount == 0)
	{
		cout << "You don't have any account" << endl;
		return false;
	}
	int n = 1;
	vector<UserAccount*>::iterator it = BankAccount.begin();
	for (it; it != BankAccount.end(); it++)
	{
		cout << n << ":";
		(*it)->Output();
	}
	int selection;
	cout << "Choice your account: ";
	cin >> selection;
	it = BankAccount.begin();
	BankAccount.erase(it+n-1);
	numOfAccount--;
	cout << "Erase successfully" << endl;
	return true;
}

bool Client::operator==(const Client *&a)
{
	if (a->SocialID == this->SocialID)
	{
		return true;
	}
	return false;
}

string Client::createPassword()
{
	stringstream password;
	int n = strlen(SocialID.c_str());
	for (int i = n - 4; i < n; i++)
	{
		password << SocialID[i];
	}
	password << setfill('0') << setw(2) << DoB.getMDay() ;
	password << setfill('0') << setw(2) << DoB.getMMonth();

	return password.str();
}

char asciitolower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

string Client::createUserName()
{	
	stringstream temp;
	temp << name;
	temp << setfill('0') << setw(2) << DoB.getMDay();
	temp << setfill('0') << setw(2) << DoB.getMMonth();
	string UserName = temp.str();
	for (int i = 0; i < UserName.length(); i++)
	{
		

		if (UserName[i] == ' ')
		{
			UserName.erase(UserName.begin()+i);
			i--;
			continue;

		}
		UserName[i] = asciitolower(UserName[i]);

	}
	return UserName;
}

void Client::display()
{
	cout << "Name: " << name << endl;
	cout << "Social ID: " << SocialID << endl;
	cout << "Address: " << address << endl;

}

UserAccount* Client::findAccount(string numID)
{
	for (vector <UserAccount*>::iterator it = BankAccount.begin(); it != BankAccount.end(); it++)
	{
		if ((*it)->getNumID() == numID)
		{
			return *it;
		}
	}
	return NULL;
}

bool Client::changeBalance(string numID, double value)
{
	UserAccount* a = Client::findAccount(numID);
	if (a == NULL)
	{
		cout << "Does not have any account with this number ID" << endl;
		return 0;
	}
	if (a->changeBalance(value) == 0)
	{
		cout << "Balance does not have enought!!" << endl;
		return 0;
	}
	cout << "Successfully" << endl;
	return 1;
}



	