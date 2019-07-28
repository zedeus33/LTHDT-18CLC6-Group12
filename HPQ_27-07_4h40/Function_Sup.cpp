#include "Function_Sup.h"
#include "LoadSaveData.h"
#define STAFF_PASSWORD "D:/StaffPassword.txt"
vector <Bank*> b;

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
				cout << "*NOTE*" << endl;
				cout << setw(30) <<"YOUR BALANCE: " << fixed << setprecision(2) <<customer->getBalance() << endl;
				cout << setw(30) << "MAX MONEY TRANSFER ONCE: " << fixed << setprecision(2) << customer->getLimit() << endl << endl;
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
		//MenuOthertasks(customer);
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