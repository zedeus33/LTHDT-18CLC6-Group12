#pragma warning(disable:4996)
#include "Function_Sup.h"
#include "Bank.h"
#include "File.h"
#define STAFF_PASSWORD "D:/StaffPassword.txt"
const string DATA_BANK = "D:/TaLangBanking/Data/Bank/";
const string DATA_ACCOUNTCLIENT = "D:/TaLangBanking/Data/Client/Account/";
const string DATA_PROFILECLIENT = "D:/TaLangBanking/Data/Client/Profile/";
vector <Bank*> b;

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
		UserAccount *useracc = new UserAccount(work[0], work[1], work[0], stod(work[2]), stod(line),cl);
		bankAcc.push_back(useracc);
	}

	cl->setBankAccount(bankAcc);
	return cl;
}
void loadDataBank(vector <Bank*> &b)
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
		b.push_back(x);
	}
}
void notice(string sentence, string horizontal = "=", string vertical = "=")
{
	cout << setw(90);
	for (int i = 0; i < ((sentence.size() + 4) / horizontal.size()); i++)
	{
		cout << horizontal;
	}
	if (horizontal.size() == 2 && sentence.size() % 2 != 0)
	{
		cout << horizontal[0];
	}
	cout << "\n";
	if (horizontal.size() == 2)
	{
		cout << setw(89);
	}
	else
	{
		cout << setw(90);
	}
	cout << vertical << " " << sentence << " " << vertical << "\n";
	cout << setw(90);
	for (int i = 0; i < ((sentence.size() + 4) / horizontal.size()); i++)
	{
		cout << horizontal;
	}
	if (horizontal.size() == 2 && sentence.size() % 2 != 0)
	{
		cout << horizontal[0];
	}
	cout << "\n";
}

bool checkStringExist(vector<string> x,string y)
{
	for (int i = 0; i < x.size(); i++)
	{
		if (x[i] == y)
		{
			return true;
		}
	}
	return false;
}

string fun_randomChar(int amount)
{
	char c;
	int r;
	string temp;
	srand(time(NULL));    // initialize the random number generator
	for (int i = 0; i < amount; i++)
	{
		r = rand() % 10;   // generate a random number
		c = '0' + r;            // Convert to a character from a-z
		temp = temp + c;
	}
	return temp;
}

string createDefaultUserID()
{
	vector <Client*> User;
	vector <string> UserID_Exist;
	for (int i = 0; i < b.size(); i++)
	{
		b[i]->setCustomer(User);
		for (int j = 0; j < User.size(); j++)
		{
			UserID_Exist.push_back(User[j]->getUserID());
		}
		b[i]->setCustomer(User);
	}
	string UserID;
	{
		UserID = fun_randomChar(4);
	} while (checkStringExist(UserID_Exist,UserID)==true);
	return UserID;
}

string createDefaultNumID()
{
	vector <Client*> User;
	vector <UserAccount*> bankAccount;
	vector <string> NumID_Exist;
	for (int i = 0; i < b.size(); i++)
	{
		b[i]->setCustomer(User);
		for (int j = 0; j < User.size(); j++)
		{
			User[j]->setBankAccount(bankAccount);
			for (int k = 0; k < bankAccount.size(); k++)
			{
				NumID_Exist.push_back(bankAccount[k]->getNumID());
			}
			User[j]->setBankAccount(bankAccount);
		}
		b[i]->setCustomer(User);
	}
	string NumID;
	do
	{
		NumID = fun_randomChar(12);
	} while (checkStringExist(NumID_Exist, NumID) == true);
	return NumID;
}

bool isDouble(string in)
{
	std::istringstream iss(in);
	double f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
	// Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

double toDouble(string in)
{
	std::istringstream iss(in);
	double f;
	iss >> noskipws >> f;
	return f;
}

UserAccount * findUserAccount(string numID)
{
	vector <Client*> cus;
	UserAccount *x = NULL;
	for (int i = 0; i < b.size(); i++)
	{
		b[i]->setCustomer(cus);
		for (int j = 0; j < cus.size(); j++)
		{
			x = cus[j]->findAccount(numID);
			if (x!=NULL)
			{
				b[i]->setCustomer(cus);
				return x;
			}
		}
		b[i]->setCustomer(cus);
	}
	return x;
}

void transfer(UserAccount * &customer)
{
	string numID;
	cout << "Please enter ID number to transfer: ";
	cin >> numID;
	UserAccount *numIDTransferTo = findUserAccount(numID);
	if (numIDTransferTo!=NULL)
	{
		system("cls");
		cout << "*************************************************************" << endl;
		cout << "\t\t\tINFORMATION NUMBER ID" << endl;
		cout << "      Name: " << numIDTransferTo->getRef()->getName() << endl;
		cout << " Number ID: " << numIDTransferTo->getNumID() << endl;
		cout << "*************************************************************" << endl << endl;
		string choice;
		cout << "Are you sure to transfer(yes/no) >> ";
		cin >> choice;
		if (_stricmp(choice.c_str(),"yes") == 0)
		{
			system("cls");
			bool ans;
			double value;
			do
			{
				string input;
				cout << "Enter value to transfer: ";
				cin >> input;
				ans = isDouble(input);
				if (ans == true)
				{
					value = toDouble(input);
				}
				else
				{
					notice("Error type,Please try again", "-", "-");
				}
			} while (ans == false);
			ans = customer->transfer(numIDTransferTo, value);
			if (ans == true)
			{
				notice("Transfer Successfully");
			}
			else
			{
				notice("Your input value is not allowed", "+", "-");
				notice("The transfer money need to be bigger than your balance and smaller than limit of transfer/time ", "+", "-");
			}
		}
		else
		{
			return;
		}
		
	}
	else
	{
		notice("This ID number doesn't exist -.-", "+", "-");
	}
}


int chooseInt(int m)
{
	int n;
	cout << "\n\nEnter your choice : ";
	cin >> n;
	while (n <= 0 || n > m)
	{
		cout << "\nWrong choice! Please try again!" << endl;
		system("pause");
		cout << "\nEnter your choice : ";
		cin >> n;
	}
	return n;
}
void MainMenu()
{
	loadDataBank(b);
	cout << "***TA LANG BANKING***" << endl;
	cout << "\n1.Sign in" << endl;
	cout << "2.Sign up" << endl;
	cout << "3.News" << endl;
	cout << "4.Exchange rate" << endl;
	cout << "5.Interest rate" << endl;
	cout << "6.Contact" << endl;
	cout << "7.Exit" << endl;
	int  choose;
	choose = chooseInt(7);
	switch (choose)
	{
	case 1:
	{
		system("cls");
		MenuSignIn();
	}break;
	case 2:
	{

	}break;
	case 3:
	{

	}break;
	case 4:
	{

	}break;
	case 5:
	{

	}break;
	case 6:
	{

	}break;
	case 7:
	{
		system("cls");
		cout << "Goodbye, Have a nice day!" << endl;
		system("pause");
		char temp = getchar();
		exit(0);
	}/*break;*/
	/*default:
	{
		cout << "Wrong choice! Please try again!" << endl;
		MainMenu();
	}*/
	}
}
void MenuSignIn()
{
	cout << "1.Log in" << endl;
	cout << "2.Return" << endl;
	int choose;
	choose = chooseInt(2);
	switch (choose)
	{
	case 1: {
		system("cls");

		string id;
		string password;
		inputIDPassword(id, password);
		UserAccount *cus= NULL;
		bool CheckPass;
		system("cls");
		if (id[0] == 'a')
		{
			CheckPass = checkLoginAdmin(id, password, STAFF_PASSWORD);
			if (CheckPass)
			{
				AdminMenu(id);
			}
			else {
				system("color c");
				cout << "\n\nWrong id or password!! Please try again" << endl;
				system("pause");

				system("color f");
				MenuSignIn();
			}
		}
		else if ((id[0] - '0') >= 0 && (id[0] - '0') <= 9)
		{
			cus = checkLoginUser(id, password);
			if (cus!=NULL)
			{
				UserMenu(cus);
			}
			else {
				system("color c");
				cout << "\n\nWrong id or password!! Please try again" << endl;
				system("pause");
				system("color f");
				MenuSignIn();
			}
		}
		else
		{

		}

	}break;
	case 2: {
		system("cls");
		MainMenu();
	}
	}
}
void UserMenu(UserAccount *&customer)
{
	cout << "1.User's information" << endl;
	cout << "2.Transfer" << endl;
	cout << "3.Payment" << endl;
	cout << "4.Deal history" << endl;
	cout << "5.Other tasks" << endl;
	cout << "6.Adjust limit" << endl;
	cout << "7.Saving" << endl;
	cout << "8.Sign out" << endl;
	int choose = chooseInt(8);
	switch (choose)
	{
	case 1:
	{
		system("cls");
		customer->Output();
		//MenuUserInfor();
	}break;
	case 2:
	{
		
		system("cls");
		transfer(customer);
		//MenuTransfer();
		string ans;
		cout << "Do you want to continue?";
		cin >> ans;
		if (ans == "yes")
		{
			UserMenu(customer);
		}
		else {
			MainMenu();
		}
	}break;
	case 3:
	{
		system("cls");
		//MenuPayment();
	}break;
	case 4:
	{
		system("cls");
		//MenuDealHistory();
	}break;
	case 5:
	{
		system("cls");
		//MenuOthertasks();
	}break;
	case 6:
	{
		system("cls");
		//MenuAdjustLimit();
	}break;
	case 7:
	{
		system("cls");
		//MenuSaving();


	}break;
	case 8:
	{
		system("cls");
		MainMenu();
	}
	}
}
bool checkLoginAdmin(string& account, string& password, const char* path) 
{
	ifstream fout;
	fout.open(path);
	string id, pw;
	while (!fout.eof())
	{
		getline(fout, id, ',');
		getline(fout, pw, '\n');
		/*if ((id) == sha1(account) && (pw) == sha1(password)) {
			return true;
		}*/
		if (id == account && pw == password) {
			return true;
		}
	}
	return false;
}
UserAccount *checkLoginUser(string id, string password)
{
	vector <Client*> User;
	vector <UserAccount*> bankAccount;
	UserAccount* temp = NULL;
	for (int i = 0; i < b.size(); i++)
	{
		b[i]->setCustomer(User);
		for (int j = 0; j < User.size(); j++)
		{
			User[j]->setBankAccount(bankAccount);
			for (int k = 0; k < bankAccount.size(); k++)
			{
				
				if (bankAccount[k]->getUsername() == id && bankAccount[k]->getPassword()==password)
				{
					temp = bankAccount[k];
					User[j]->setBankAccount(bankAccount);
					b[i]->setCustomer(User);
					return temp;
				}
			}
			User[j]->setBankAccount(bankAccount);
		}
		b[i]->setCustomer(User);
	}
	return temp;
}
void AdminMenu(string id)
{

}
void inputIDPassword(string& id, string& password)
{
	cout << "\n\n\n" << endl;
	system("color a");
	std::cout << "\t\t\tInput ID :       ";
	cin >> id;
	std::cout << "\t\t\tInput password : ";

	char pass;
	string temp;
	do
	{
		pass = _getch();
		if (pass == '\n' || pass == '\r')
		{
			cout << "\n";
			break;
		}
		else if (pass == '\b')
		{
			cout << "\b \b";
			if (temp.empty() == false)
			{
				temp.erase(temp.size() - 1);
			}
		}
		else if (pass == -32)
		{
			_getch();
		}
		else if (isprint(pass) && temp.size() < 10)
		{
			cout << "*";
			temp = temp + pass;
		}
	} while (true);
	password = temp;
	system("color f");
}

