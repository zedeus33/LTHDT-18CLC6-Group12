#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include "Function_Sup.h"
#include "Behaviors.h"
#include "LoadSaveData.h"
#include "PaymentElectricBill.h"
#include "PaymentWaterBill.h"
#include "BlackList.h"
#include <io.h>
const string DATA_EXRATE = "Exrate.txt";
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

bool isNum(string in)
{
	for (char c : in)
	{
		if (c < '0' || c > '9')
			return false;
	}
	return true;
}

int toInt(string in)
{
	stringstream is;
	is << in;
	int ans;
	is >> ans;
	return ans;
}

int chooseInt(int m)
{
	string n;
	cout << "\n\nEnter your choice : ";
	cin >> n;
	try {
		if (toInt(n) > 0 && toInt(n) <= m && isNum(n))
		{
			return toInt(n);
		}
		else {
			throw "\nSomething went wrong!";
		}
	}
	catch (const char* a)
	{
		cout << a << endl;
		return chooseInt(m);
	}
	
}
void MainMenu()
{
	BlackList* bl = BlackList::getBlackList();
	bl->loadBlackList(BLACK_LIST.c_str());
	if (b.empty())
	{
		loadDataBank(b);
	}
	cout << "***TA LANG iBANKING***" << endl;
	cout << "\n[1]. Sign in" << endl;
	cout << "[2]. Sign up" << endl;
	cout << "[3]. News" << endl;
	cout << "[4]. Exchange rate" << endl;
	cout << "[5]. Interest rate" << endl;
	cout << "[6]. Contact" << endl;
	cout << "[7]. Exit" << endl;
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
		system("cls");
		MenuSignUp();
	}break;
	case 3:
	{

	}break;
	case 4:
	{
		exchangeRate();
		MainMenuContinue();
	}break;
	case 5:
	{
		system("cls");
		outputInterestRate(INTEREST_RATES_FILE);
		MainMenuContinue();
	}break;
	case 6:
	{
		system("cls");
		outPutContact(CONTACT_FILE);
		MainMenuContinue();
	}break;
	case 7:
	{
		exit();
	}
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
		UserAccount* cus = NULL;
		bool CheckPass;
		system("cls");
		if (id[0] == 'a')
		{
			CheckPass = checkLoginAdmin(id, password, STAFF_PASSWORD);
			if (CheckPass)
			{
				system("cls");
				Admin* p = new Admin(id, password);
				AdminMenu(p);
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
			if (cus == NULL) {
				system("color c");
				cout << "\n\nWrong id or password!! Please try again" << endl;
				system("pause");
				system("color f");
				MenuSignIn();
			}
			else {
				Behaviors* p = new LoginBehavior();
				p->saveLog(p->toString().c_str(),bh_mkdir(cus).c_str());
				p->sentOTP(cus->getRefClient()->getEmail());
				if (checkOTP(p) == true)
				{
					system("cls");
					notice("Welcome", "+", "+");
					UserMenu(cus);
				}
				else {
					system("color c");
					cout << "\n\nWrong OTP or OTP has been expired! Please try again!" << endl;
					system("pause");
					system("color f");
					MenuSignIn();
				}
			}
		}
		else
		{
			system("color c");
			cout << "\n\nWrong input!! Please try again" << endl;
			system("pause");

			system("color f");
			MenuSignIn();
		}

	}break;
	case 2: {
		system("cls");
		MainMenu();
	}
	}
}
void UserMenu(UserAccount*& customer)
{
	cout << "[1]. User's information" << endl;
	cout << "[2]. Transfer" << endl;
	cout << "[3]. Payment" << endl;
	cout << "[4]. Deal and login history" << endl;
	cout << "[5]. Other tasks" << endl;
	cout << "[6]. Adjust limit" << endl;
	cout << "[7]. Saving" << endl;
	cout << "[8]. Sign out" << endl;
	int choose = chooseInt(8);
	switch (choose)
	{
	case 1:
	{
		system("cls");
		customer->Output();
		UserMenuContinue(customer);
		//MenuUserInfor();
	}break;
	case 2:
	{
		system("cls");
		transfer(customer);
		UserMenuContinue(customer);
		//MenuTransfer();
	}break;
	case 3:
	{
		system("cls");
		//MenuPayment(customer);
		MenuPayment(customer);
		//MenuPayment();
	}break;
	case 4:
	{
		system("cls");
		//MenuDealHistory();
		vector <Behaviors*> customer_behaviors;
		customer_behaviors = ReadData(customer);
		for (auto& i : customer_behaviors)
		{
			cout << i->toScreen() << endl;
		}
		cout << endl;
		UserMenuContinue(customer);
	}break;
	case 5:
	{
		system("cls");
		MenuOthertasks(customer);
	}break;
	case 6:
	{
		system("cls");
		//MenuAdjustLimit();
	}break;
	case 7:
	{
		system("cls");
		MenuSaving(customer);
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
UserAccount* checkLoginUser(string id, string password)
{
	BlackList::clear();
	BlackList* bl = BlackList::getBlackList();
	bl->loadBlackList(BLACK_LIST.c_str());
	if (bl->isBlock(id))
		return nullptr;
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

				if (bankAccount[k]->getUsername() == id && bankAccount[k]->getPassword() == password)
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
void AdminMenu(Admin *p)
{
	system("cls");
	cout << "[1]. Block User" << endl;
	cout << "[2]. View User History" << endl;
	cout << "[3]. View User Account create Request" << endl;
	cout << "[4]. UnLock User" << endl;
	cout << "[5]. View Block User Request" << endl;
	cout << "[6]. Return " << endl;
	int choose = chooseInt(6);
	switch (choose)
	{
	case 1:
	{
		system("cls");
		string numID;
		cout << "Please enter numID of Account to block: ";
		cin >> numID;
		UserAccount* rha = p->searchUserAccount(b, numID);
		if (rha == nullptr)
		{
			cout << "Num ID is not exist !" << endl;
			MenuAdminContinue(p);
			break;
		}
		BlackList::clear();
		BlackList* bl = BlackList::getBlackList();
		bl->loadBlackList(BLACK_LIST.c_str());
		bool ans = p->blockUser(rha);
		if (ans)
		{
			cout << "Block user " << numID << " successfully!" << endl;
		}
		else
			cout << " Something went wrong!" << endl;
		bl->saveBlackList(BLACK_LIST.c_str());
		MenuAdminContinue(p);
		
	}break;
	case 2:
	{
		system("cls");
		string numID;
		cout << "Please enter User Account ID to view history: ";
		cin >> numID;
		UserAccount* rha = p->searchUserAccount(b, numID);
		p->viewUserHistoryLog(rha);
		MenuAdminContinue(p);
		
	}break;
	case 3:
	{
		system("cls");
		p->viewRequestLog(b);
		MenuAdminContinue(p);
		
	}break;
	case 4:
	{
		system("cls");
		string numID;
		cout << "Please enter numID of Account to unlock: ";
		cin >> numID;
		UserAccount* rha = p->searchUserAccount(b, numID);
		if (rha == nullptr)
		{
			cout << "Num ID is not exist !" << endl;
			MenuAdminContinue(p);
			break;
		}
		BlackList::clear();
		BlackList* bl = BlackList::getBlackList();
		bl->loadBlackList(BLACK_LIST.c_str());
		bool ans = p->unBlockUser(rha);
		if (ans)
		{
			cout << "Unlock user " << numID << " successfully!" << endl;
		}
		else
			cout << "Num ID is not exist or something went wrong!" << endl;
		bl->saveBlackList(BLACK_LIST.c_str());
		MenuAdminContinue(p);
	}break;
	case 5:
	{
		system("cls");
		p->viewBlockRequestLog(b);
		MenuAdminContinue(p);
	}break;
	case 6:
	{
		system("cls");
		MenuSignIn();
		break;
	}
	}
}
void MenuPayment(UserAccount *& cus)
{
	cout << "[1]. Electric bill" << endl;
	cout << "[2]. Water bill" << endl;
	cout << "[3]. Return" << endl;
	string note;
	int n = chooseInt(3);
	system("cls");
	switch (n)
	{
	case 1:
	{
		Payment *p = new PaymentElectricBill();
		note = p->paymentBill(cus);
		if (note!="return")
		{
			notice(note, "~", "|");
		}
		MenuPaymentContinue(cus);
	}break;
	case 2:
	{
		Payment *p = new PaymentWaterBill();
		note = p->paymentBill(cus);
		if (note != "return")
		{
			notice(note, "~", "|");
		}
		MenuPaymentContinue(cus);
	}break;
	case 3:
	{
		system("cls");
		UserMenu(cus);
	}

	}
	
}

void MenuOthertasks(UserAccount*& customer)
{
	cout << "[1]. Change password" << endl;
	cout << "[2]. Bank system's address" << endl;
	cout << "[3]. News" << endl;
	cout << "[4]. Exchange rate" << endl;
	cout << "[5]. Interest rate" << endl;
	cout << "[6]. Create new Account" << endl;
	cout << "[7]. Block this Account" << endl;
	cout << "[8]. Return" << endl;
	int n = chooseInt(8);
	switch (n)
	{
		case 1:
		{
			system("cls");
			if (changePassword(customer)) {
				system("pause");
				cout << "Your password has been changed succesfully! Please log out and log in again with new password!" << endl;
				system("pause");
				system("cls");
				MenuSignIn();
			}
			else {
				cout << "Something went wrong! Your new password is too short or too long! Please try again!" << endl;
				MenuOtherTasksContinue(customer);
			}
		}break;
		case 2:
		{
			system("cls");
			for (int i = 0; i < b.size(); i++)
			{
				b[i]->show_infor();
			}
			MenuOtherTasksContinue(customer);
		}break;
		case 3:
		{

		}break;
		case 4:
		{
			system("cls");
			exchangeRate();
			MenuOtherTasksContinue(customer);
		}break;
		case 5:
		{
			system("cls");
			outputInterestRate(INTEREST_RATES_FILE);
			MenuOtherTasksContinue(customer);
		}break;
		case 6:
		{
			system("cls");
			Client* p = customer->getRefClient();
			saveRequireNewUserAccount(p);
			cout << "Your request have been sent to our server. We will sent you a messege when the task finish!" << endl;
			MenuOtherTasksContinue(customer);
		}break;
		case 7:
		{
			system("cls");
			Client* p = customer->getRefClient();
			saveRequiredBlockUserAccount(p,customer);
			cout << "Your request have been sent to our server. We will sent you a messege when the task finish!" << endl;
			MenuOtherTasksContinue(customer);
		}break;
		case 8:
		{
			system("cls");
			UserMenu(customer);
		}
	
	}

}
void MenuSaving(UserAccount *cur)
{
	
	cout << "[1]. Create saving with period." << endl;
	cout << "[2]. Create saving without period" << endl;
	cout << "[3]. Check saving book" << endl;
	cout << "[4]. Return" << endl;
	int n = chooseInt(4);
	switch (n)
	{
	case 1:
	{
		double money;
		cout << "Input money you want to saving : ";
		cin >> money;
		int period;
		cout << "Input your period(month) : ";
		cin >> period;
		period = period;
		if (cur->CreateSavingPeriod(money, period))
		{
			cout << "Create saving book with period " << period << " day successfully!" << endl;
		}
		else
		{
			MenuSavingContinue(cur);
		}
		MenuSavingContinue(cur);
	}break;
	case 2:
	{
		double money;
		cout << "Input money you want to saving : ";
		cin >> money;
		if (cur->CreateSavingNoPeriod(money))
		{
			cout << "Create saving book without period successfully!" << endl;
		}
		else
		{
			MenuSavingContinue(cur);
		}
		MenuSavingContinue(cur);
	}break;
	case 3:
	{
		cout << "You have " << cur->getListsize() << " saving book!" << endl;
		cur->outputList();
		system("pause");
		MenuSavingContinue(cur);
	}break;
	case 4:
	{
		system("cls");
		UserMenu(cur);
	}
	}

}
void MenuSignUp()
{
	for (int i = 0; i < b.size(); i++)
	{
		b[i]->show_infor();
	}
	int n = chooseInt(4);
	switch (n)
	{
		case 1:
		{
			system("cls");
			b[0]->addNewUser();
		}break;
		case 2:
		{
			system("cls");
			b[1]->addNewUser();
		}break;
		case 3:
		{
			system("cls");
			b[2]->addNewUser();
		}break;
		case 4:
		{
			system("cls");
			b[3]->addNewUser();
		}
	}
	MainMenuContinue();
}

void exit()
{
	system("cls");
	cout << "Goodbye, Have a nice day!" << endl;
	system("pause");
	char temp = getchar();
	saveDataBank(b);
	exit(0);
}

void MainMenuContinue()
{

	cout << "\nDo you want to continue? (y = Yes , n = No)";
	string YesOrNo;
	cin >> YesOrNo;
	if (YesOrNo == "y")
	{
		system("cls");
		MainMenu();
	}
	else if (YesOrNo == "n")
	{
		exit();
	}
	else
	{
		system("cls");
		notice("Wrong input! Please try again", "+", "+");
		system("pause");
		MainMenuContinue();
	}
}
void MenuOtherTasksContinue(UserAccount *&cus)
{
	cout << "\nDo you want to continue? (y = Yes , n = No) : ";
	string YesOrNo;
	cin >> YesOrNo;
	if (YesOrNo == "y")
	{
		system("cls");
		MenuOthertasks(cus);
	}
	else if (YesOrNo == "n")
	{
		exit();
	}
	else
	{
		system("cls");
		notice("Wrong input! Please try again", "+", "+");
		system("pause");
		MainMenuContinue();
	}
}
void UserMenuContinue(UserAccount *& cus)
{
	cout << "\nDo you want to continue? (y = Yes , n = No) : ";
	string YesOrNo;
	cin >> YesOrNo;
	if (YesOrNo == "y")
	{
		system("cls");
		UserMenu(cus);
	}
	else if (YesOrNo == "n")
	{
		exit();
	}
	else
	{
		system("cls");
		notice("Wrong input! Please try again", "+", "+");
		system("pause");
		UserMenuContinue(cus);
	}
}
void MenuPaymentContinue(UserAccount *& cus)
{
	cout << "Do you want to continue? (y = Yes , n = No) : ";
	string YesOrNo;
	cin >> YesOrNo;
	if (YesOrNo == "y")
	{
		system("cls");
		MenuPayment(cus);
	}
	else if (YesOrNo == "n")
	{
		exit();
	}
	else
	{
		system("cls");
		notice("Wrong input! Please try again", "+", "+");
		system("pause");
		MenuPaymentContinue(cus);
	}
}
void MenuSavingContinue(UserAccount* cus)
{
	cout << "Do you want to continue? (y = Yes , n = No) : ";
	string YesOrNo;
	cin >> YesOrNo;
	if (YesOrNo == "y")
	{
		system("cls");
		MenuSaving(cus);
	}
	else if (YesOrNo == "n")
	{
		system("cls");
		UserMenu(cus);
	}
	else
	{
		system("cls");
		notice("Wrong input! Please try again", "+", "+");
		system("pause");
		MenuSavingContinue(cus);
	}
}
void MenuAdminContinue(Admin* a)
{
	cout << "Do you want to continue? (y = Yes , n = No) : ";
	string YesOrNo;
	cin >> YesOrNo;
	if (YesOrNo == "y")
	{
		system("cls");
		AdminMenu(a);
	}
	else if (YesOrNo == "n")
	{
		system("cls");
		MenuSignIn();
	}
	else
	{
		system("cls");
		notice("Wrong input! Please try again", "+", "+");
		system("pause");
		MenuAdminContinue(a);
	}
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
		else if (isprint(pass) && temp.size() < 8)
		{
			cout << "*";
			temp = temp + pass;
		}
	} while (true);
	password = temp;
	system("color f");
}

bool changePassword(UserAccount*& a)
{
	cout << "Enter new password : ";
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
		else if (isprint(pass) && temp.size() <= 8)
		{
			cout << "*";
			temp = temp + pass;
		}
	} while (true);
	if (temp.size() == 8)
	{
		Behaviors* p = new ChangePWBehavior();
		p->sentOTP(a->getRefClient()->getEmail());
		if (checkOTP(p) == true)
		{
			p->saveLog(p->toString().c_str(), bh_mkdir(a).c_str());
			a->setPassword(temp);
			cout << "Your new password is : " << temp << endl;
			return true;
		}
		return false;
	}
	else return false;
	
}

string deleteChar(string content, char character)
{
	stringstream temp;
	for (int i = 0; i < content.size(); i++)
	{
		if (content[i] != character)
		{
			temp << content[i];
		}
	}
	return temp.str();
}

bool alnum(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return 0;
		}
	}
	return 1;
}

void checkSocialID(const string& id)
{
	if (id.length() != 9)
	{
		throw "Length ERROR";
	}
	if (alnum(id) == 0)
	{
		throw "Type ERROR \n Type Expected: NUMBER";
	}
}

void checkEmail(const string& email)
{
	for (int i = 0; i < email.length(); i++)
	{
		if (email[i] == '@')
		{
			if (i == 0)
			{
				throw "Invalid Email!!Please try again~";
			}
			else
			{
				return;
			}
		}

	}
	throw "Invalid Email!!Please try again~";

}

string inputSocialID(string SocialID, const char* text)
{
	do
	{
		cout << text;
		getline(cin, SocialID, '\n');
		try
		{
			checkSocialID(SocialID);
			break;
		}
		catch (const char* error)
		{
			cout << error << endl;
		}
	} while (true);
	return SocialID;
}

string inputEmail(string Email, const char* text)
{
	do
	{
		cout << text;
		getline(cin, Email, '\n');
		try
		{
			checkEmail(Email);
			break;
		}
		catch (const char* error)
		{
			cout << error << endl;
		}
	} while (true);
	return Email;
}



bool checkStringExist(vector<string> x, string y)
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
	} while (checkStringExist(UserID_Exist, UserID) == true);
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
float InputFloat(float& a, const char* text)
{
	bool check;
	float  temp;
	do
	{
		stringstream iss;
		string sInput;
		cout << text;
		getline(cin, sInput, '\n');
		iss << sInput;
		iss >> temp;
		check = iss.eof() && !iss.fail();
		if (check == 0)
		{
			cout << "WRONG TYPE__TYPE EXPECTED: NUMBER" << endl;
			cout << "Please try again!" << endl;
			continue;
		}
		else
		{
			a = temp;
			return a;
		}
	} while (true);
}

int InputInt(int& a, const char* text)
{
	int temp;
	bool check;
	do
	{
		string sInput;
		stringstream iss;
		cout << text;
		getline(cin, sInput, '\n');
		iss << sInput;
		iss >> temp;
		check = iss.eof() && !iss.fail();
		if (check == 0)
		{
			cout << "WRONG TYPE__TYPE EXPECTED: NUMBER" << endl;
			cout << "Please try again!" << endl;
			continue;
		}
		else
		{
			a = temp;
			return a;
		}
	} while (true);
}

bool InputBool(bool& a, const char* text)
{
	bool temp;
	bool check;
	do
	{
		string sInput;
		cout << text;
		getline(cin, sInput, '\n');
		if (sInput == "0")
		{
			temp = 0;
			a = temp;
			return temp;
		}
		else if (sInput == "1")
		{
			temp = 1;
			return a;
		}
		else
		{
			cout << "WRONG TYPE__TYPE EXPECTED: BOOL" << endl;
			cout << "Please try again!" << endl;
		}
	} while (true);
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
			if (x != NULL)
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
	if (numIDTransferTo != NULL)
	{
		if (numIDTransferTo==customer)
		{
			notice("YOU SO STUPID,CAN'T TRANSFER TO YOUR OWN ACCOUNT =))))");
			return;
		}
		string name = numIDTransferTo->getRefClient()->getName();
		string numID = numIDTransferTo->getNumID();
		cout << "--------------------------------------------------" << endl;
		cout << "|" << setw(20+15) << "INFORMATION NUMBER ID" << setw(60-36-10)<< "|"<< endl;
		cout << "--------------------------------------------------" << endl;
		cout << "|     Name: " << name << setw(60-12-name.size()-10) << "|" << endl;
		cout << "|Number ID: " << numID << setw(60-12-numID.size()-10) << "|" << endl;
		cout << "--------------------------------------------------" << endl << endl;
		string choice;
		cout << "Are you sure to transfer(yes/no) >> ";
		cin >> choice;
		if (_stricmp(choice.c_str(), "yes") == 0)
		{
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
				notice("TRANSFER SUCCESSFULLY ^.^");
			}
			else
			{
				notice("YOUR BALANCE IS NOT ENOUGH OR OVER THE LIMIT OF TRANSFER -.-", ".", ".");
			}
		}
		else if(_stricmp(choice.c_str(), "no") == 0)
		{
			return;
		}
		else
		{
			notice("ERROR TYPE -.-");
		}
	}
	else
	{
		notice("This ID number doesn't exist -.-", ".", ".");
	}
}

void outPutContact(const char* path)
{
	fstream file;
	file.open(path);
	if (_access(path, 0) == -1)
	{
		cout << "ERROR:COUND NOT FOUND" << path << "FILE" << endl;
		return;
	}
	cout << "\t\t\t|Contact|" << endl;
	cout << "\t\t\t---------" << endl;
	cout << "|Name|" << "\t\t\t" << "|Phone number|" << endl;
	cout << "------" << "\t\t\t" << "--------------" << endl;
	while (!file.eof())
	{
		string name;
		string phoneNum;
		getline(file, name, '/');
		getline(file, phoneNum, '\n');
		cout << setw(25) << left << name << setw(25) << left << phoneNum << endl;
		cout << "======================================" << endl;
	}
	file.close();
}

void exchangeRate()
{
	system("wget -O Exrate.txt https://www.vietcombank.com.vn/exchangerates/ExrateXML.aspx");
	system("cls");
	string time;
	string date = readline((DATA_EXRATE.c_str()), 4);
	cout << "\t\t\t\t\tEXCHAGE RATE\n";
	date.erase(date.begin(), date.begin() + 12);
	auto x = date.find_first_of(' ');
	time = date.substr(x + 1, date.size());
	date.erase(date.begin() + x, date.end());
	time.erase(time.end() - 11, time.end());
	cout << "Date: " << date << " Time: " << time << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << setw(14) << "|Currency Code|" << setw(20) << "Currency Name|" << setw(10) << "Buy|" << setw(10) << "Transfer|" << setw(10) << "Sell|" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	for (int i = 0; i < 19; i++)
	{
		string temp = readline(DATA_EXRATE.c_str(), i + 5);
		string Code = temp.substr(24, 3);
		temp.erase(temp.begin(), temp.begin() + 29);
		x = temp.find("Buy");
		string Name = temp.substr(14, x - 16);
		temp.erase(temp.begin(), temp.begin() + x);
		x = temp.find_first_of(' ');
		string buy = temp.substr(5, x - 6);
		temp.erase(temp.begin(), temp.begin() + x + 1);
		x = temp.find_first_of(' ');
		string transfer = temp.substr(10, x - 11);
		temp.erase(temp.begin(), temp.begin() + x + 1);
		x = temp.find_first_of(' ');
		string sell = temp.substr(6, x - 7);
		cout << "|" << setw(13) << Code << "|" << setw(19) << Name << "|" << setw(9) << buy << "|" << setw(9) << transfer << "|" << setw(9) << sell << "|" << endl;
		cout << "-----------------------------------------------------------------" << endl;
	}
	system("del /f Exrate.txt");
}

void outputInterestRate(const char* path)
{
	fstream file;
	file.open(path);
	if (_access(path, 0) == -1)
	{
		cout << "ERROR:COUND NOT FOUND  " << path << " File" << endl;
		return;
	}
	cout << "\t\t\t\t\t\t----------------" << endl;
	cout << "\t\t\t\t\t\t|Interest Rates|" << endl;
	cout << "\t\t\t\t\t\t----------------" << endl;
	string object1;
	string object2;
	string tenor;
	string vnd1, usd1, eur1;
	string vnd2, usd2, eur2;
	getline(file, tenor, ',');
	getline(file, object1, ',');
	file.ignore();
	file.ignore();
	getline(file, object2, '\n');
	cout << setw(18) << left << tenor << '|' << setw(54) << left << object1 << "|" << object2 << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	file.ignore();
	getline(file, vnd1, ',');
	getline(file, usd1, ',');
	getline(file, eur1, ',');
	getline(file, vnd2, ',');
	getline(file, usd2, ',');
	getline(file, eur2, '\n');
	cout << setw(18) << left << "" << '|' << setw(18) << left << vnd1 << setw(18) << left << usd1 << setw(18) << left << eur2
		<< '|' << setw(18) << left << vnd2 << setw(18) << left << usd2 << eur2 << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

	while (!file.eof())
	{

		getline(file, tenor, ',');
		getline(file, vnd1, ',');
		getline(file, usd1, ',');
		getline(file, eur1, ',');
		getline(file, vnd2, ',');
		getline(file, usd2, ',');
		getline(file, eur2, '\n');
		cout << setw(18) << left << tenor << '|' << setw(18) << left << vnd1 << setw(18) << left << usd1 << setw(18) << left << eur2 << '|' << setw(18) << left
			<< vnd2 << setw(18) << left << usd2 << eur2 << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "Unit: %" << endl;
	file.close();
}