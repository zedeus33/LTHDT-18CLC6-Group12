#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include "Function_Sup.h"
#include "File.h"
#include "Transaction.h"
#include <io.h>

#define STAFF_PASSWORD "D:/StaffPassword.txt"
const string DATA_BANK = "D:/TaLangBanking/Data/Bank/";
const string DATA_ACCOUNTCLIENT = "D:/TaLangBanking/Data/Client/Account/";
const string DATA_PROFILECLIENT = "D:/TaLangBanking/Data/Client/Profile/";
const string DATA_BEHAVIORS = "D:/TaLangBanking/Data/Behaviors";
const char* CONTACT_FILE = "D:/TaLangBanking/contact.txt";
const char* EXCHANGE_RATES_FILE = "D:/TaLangBanking/ExchangeRate.txt";
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
	Client* cl = new Client(name, addr, socialID, UserID, mail, day, sexual, stof(salary));
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
	/*while (n <= 0 || n > m)
	{
		cout << "\nWrong choice! Please try again!" << endl;
		system("pause");
		cout << "\nEnter your choice : ";
		cin >> n;
	}*/
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
		system("cls");
		MenuSignUp();
	}break;
	case 3:
	{

	}break;
	case 4:
	{
		system("cls");
		outPutExchangeRates(EXCHANGE_RATES_FILE);
		MainMenuContinue();	
	}break;
	case 5:
	{
		system("cls");
		outputInterestRate("D:/TaLangBanking/InterestRate.txt");
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
		UserAccount* cus = NULL;
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
			if (cus == NULL) {
				system("color c");
				cout << "\n\nWrong id or password!! Please try again" << endl;
				system("pause");
				system("color f");
				MenuSignIn();
			}
			else {
				Transaction* p = new LoginBehavior();
				p->Export(DATA_BEHAVIORS.c_str());
				p->sentOTP(cus->getRefClient()->getEmail());
				if (checkOTP(p) == true)
				{
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
			/*Transaction* p = new LoginBehavior();
			p->Export(DATA_BEHAVIORS.c_str());
			p->sentOTP(cus->getRefClient()->getEmail());
			if (cus != NULL && checkOTP(p) == true)
			{

				UserMenu(cus);
			}
			else {
				system("color c");
				cout << "\n\nWrong id or password!! Please try again" << endl;
				system("pause");
				system("color f");
				MenuSignIn();
			}*/
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
	cout << "[4]. Deal history" << endl;
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
		//MenuUserInfor();
	}break;
	case 2:
	{
		system("cls");
		//MenuTransfer();
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
UserAccount* checkLoginUser(string id, string password)
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
void AdminMenu(string id)
{

}
void MenuOthertasks(UserAccount*& customer)
{
	cout << "[1]. Change password" << endl;
	cout << "[2]. Bank system's address" << endl;
	cout << "[3]. News" << endl;
	cout << "[4]. Exchange rate" << endl;
	cout << "[5]. Interest rate" << endl;
	cout << "[6]. Return" << endl;
	int n = chooseInt(6);
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

		}break;
		case 5:
		{

		}break;
		case 6:
		{
			system("cls");
			UserMenu(customer);
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
		system("cls");
		cout << "Goodbye, Have a nice day!" << endl;
		system("pause");
		char temp = getchar();
		exit(0);
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
		MenuOthertasks(cus);
	}
	else if (YesOrNo == "n")
	{
		system("cls");
		cout << "Goodbye, Have a nice day!" << endl;
		system("pause");
		char temp = getchar();
		exit(0);
	}
	else
	{
		system("cls");
		notice("Wrong input! Please try again", "+", "+");
		system("pause");
		MainMenuContinue();
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
		a->setPassword(temp);
		cout << "Your new password is : " << temp << endl;
		return true;
	}
	else return false;
	
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

void outPutExchangeRates(const char* path)
{
	fstream file;
	file.open(path);
	if (_access(path, 0) == -1)
	{
		cout << "ERROR:COUND NOT FOUND "<< path << " FILE" <<endl;
		return;
	}
	cout << "\t\t\t\t\t | Exchange  Rates |" << endl;
	cout << "\t\t\t\t\t -------------------" << endl;
	cout << "Foreign Currencies" << '\t' << "Bit Rate Of Cash" << '\t' << "Bit Rate OfTransfer" << '\t'
		<< "Offer Rate Of Transfer" << '\t' << "Offer Rate Of Cash" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	while (!file.eof())
	{
		string ForeignCurrencies;
		string BitRateCash, BitRateTransfer;
		string OfferRateTransfer, OfferRateCash;
		getline(file, ForeignCurrencies, ' ');
		getline(file,BitRateCash,' ');
		getline(file, BitRateTransfer, ' ');
		getline(file, OfferRateTransfer, ' ');	
		getline(file, OfferRateCash, '\n');
		cout <<"|" <<  ForeignCurrencies << "\t\t\t" << BitRateCash << "\t\t\t" << BitRateTransfer << "\t\t\t"
			<< OfferRateTransfer << "\t\t\t" << OfferRateCash << "          |"<< endl;
		cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	}
	file.close();
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
		cout <<setw(25) << left <<name << setw(25)<< left <<  phoneNum  << endl;
		cout << "======================================" << endl;
	}
	file.close();
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