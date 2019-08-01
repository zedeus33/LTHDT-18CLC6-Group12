#include "Client.h"




Client::Client()
{
	name = "";
	address = "";
	numOfAccount = 0;
	SocialID = "";
	UserID = "";
}

vector<UserAccount*> Client::getBackAccount()
{
	return BankAccount;
}

Client::Client(string name, string addr, string SocialID, string UserID, string email, Date dob, bool sex, float salary)
{
	this->name = name;
	this->address = addr;
	this->SocialID = SocialID;
	this->UserID = UserID;
	this->Email = email;
	this->DoB = dob;
	this->Sex = sex;
	this->Salary = salary;
}

void Client::input()
{
	if (cin.get() != '\n')
		cin.ignore();
	cout << "Enter name: ";
	getline(cin, name, '\n');
	cout << "Enter Address: ";
	getline(cin, address, '\n');
	Sex = InputBool(Sex, "Sex (0:Male,1:Female):");
	cout << "Enter day of birth" << endl;
	DoB.input();
	cin.ignore();
	Salary = InputFloat(Salary, "Enter Salary: ");
	SocialID = inputSocialID(SocialID, "Enter SocialID (9 numbers): ");
	Email = inputEmail(Email, "Enter Email: ");
	UserID = createDefaultUserID();
	
	cout << "Your User ID is:" << UserID << endl;
}

void Client::input2(UserAccount* a)
{
	if (cin.get() != '\n')
		cin.ignore();
	cout << "Enter name: ";
	getline(cin, name, '\n');
	cout << "Enter Address: ";
	getline(cin, address, '\n');
	Sex = InputBool(Sex, "Sex (0:Male,1:Female):");
	Salary = a->getRefClient()->getSalary();
	/*cout << "Enter day of birth" << endl;
	DoB.input();
	cin.ignore();*/
	//Salary = InputFloat(Salary, "Enter Salary: ");
	SocialID = inputSocialID(SocialID, "Enter SocialID (9 numbers): ");
	//Email = inputEmail(Email, "Enter Email: ");
	Email = a->getRefClient()->getEmail();
	UserID = createDefaultUserID();

	cout << "Your User ID is:" << UserID << endl;
}

void Client::inputDoB()
{
	cout << "Enter day of birth" << endl;
	DoB.input();
}

void Client::output()
{
	cout << "/t/tClient information" << endl;
	cout << "Name: " << name << endl;
	cout << "Address: " << address << endl;
	cout << "Social ID: " << SocialID << endl;
	cout << "User ID: " << UserID << endl;
	cout << "Email: " << Email << endl;
	cout << "Day of Birth: " << DoB.output() << endl;
	cout << "Sex: ";
	if (Sex == 1)
	{
		cout << "Female" << endl;
	}
	else
	{
		cout << "Male" << endl;
	}
	cout << "Salary: " << fixed << setprecision(2) << Salary << endl;
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
		UserAccount* _new = new UserAccount;
		//_new->setClient(this);
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
	BankAccount.erase(it + n - 1);
	numOfAccount--;
	cout << "Erase successfully" << endl;
	return true;
}

void Client::createDefaultUserAccount()
{
	Client* rha = this;
	UserAccount* a = new UserAccount(createDefaultNumID(),this->createPassword(),createDefaultNumID(),double(0),double(0),rha);
	cout << "Your new default user number ID is :" << a->getNumID() << endl;
	cout << "Your new default username is : " << a->getUsername() << endl;
	cout << "Your new default password is : " << a->getPassword() << endl;
	BankAccount.push_back(a);
}

bool Client::operator==(const Client*& a)
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
	password << setfill('0') << setw(2) << DoB.getMDay();
	password << setfill('0') << setw(2) << DoB.getMMonth();

	return password.str();
}

string Client::getName()
{
	return name;
}

char asciitolower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

//string Client::createUserName()
//{
//	stringstream temp;
//	temp << name;
//	temp << setfill('0') << setw(2) << DoB.getMDay();
//	temp << setfill('0') << setw(2) << DoB.getMMonth();
//	string UserName = temp.str();
//	for (int i = 0; i < UserName.length(); i++)
//	{
//
//
//		if (UserName[i] == ' ')
//		{
//			UserName.erase(UserName.begin() + i);
//			i--;
//			continue;
//
//		}
//		UserName[i] = asciitolower(UserName[i]);
//
//	}
//	return UserName;
//}

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

int Client::changeBalance(string numID, double value)
{
	UserAccount* a = Client::findAccount(numID);
	if (a == NULL)
	{
		return 0;
	}
	if (a->changeBalance(value) == 0)
	{
		cout << "Balance does not have enought!!" << endl;
		return -1;
	}
	cout << "Successfully" << endl;
	return 1;
}

string Client::getEmail()
{
	return this->Email;
}

Client::Client(const Client& rha)
{
	this->name = rha.name;
	this->address = rha.address;
	this->SocialID = rha.SocialID;
	this->UserID = rha.UserID;
	this->Email = rha.Email;
	this->DoB = rha.DoB;
	this->Sex = rha.Sex;
	this->Salary = rha.Salary;
}

string Client::getAddress()
{
	return this->address;
}

string Client::getSocialID()
{
	return this->SocialID;
}

Date Client::getDob()
{
	return DoB;
}

bool Client::getSex()
{
	return this->Sex;
}

float Client::getSalary()
{
	return this->Salary;
}