#include "Sup_Function.h"
#define CLIENT_PASSWORD "E:/Garena/Games/Project1/StaffPassword.txt"
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
		/*cout << "Input ID : ";
		cin >> id;
		cout << "Input password : ";
		cin >> password;*/
		inputIDPassword(id,password);
		bool CheckPass;
		system("cls");
		CheckPass = checkLogin(id, password, CLIENT_PASSWORD);
		if (CheckPass) {
			secondMenu(id);
		}
		else {
			system("color c");
			cout << "Wrong id or password!! Please try again" << endl;
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
void secondMenu(string id)
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
	switch(choose)
	{
	case 1:
	{
		system("cls");
		MenuUserInfor();
	}break;
	case 2:
	{
		system("cls");
		MenuTransfer();
	}break;
	case 3:
	{
		system("cls");
		MenuPayment();
	}break;
	case 4:
	{
		system("cls");
		MenuDealHistory();
	}break;
	case 5:
	{
		system("cls");
		MenuOthertasks();
	}break;
	case 6:
	{
		system("cls");
		MenuAdjustLimit();
	}break;
	case 7:
	{
		system("cls");
		MenuSaving();

	}break;
	case 8:
	{
		system("cls");
		MainMenu();
	}
	}
}
bool checkLogin(string& account, string& password, const char* path) {
	ifstream fout;
	fout.open(path);
	//int aos; /*aos: Amount of firstStudentMenu,firstLectureMenu*/
	string id, pw;
	while (!fout.eof())
	{
		getline(fout, id, ',');
		getline(fout, pw, '\n');
		/*if ((id) == sha1(account) && (pw) == sha1(password)) {
			return true;
		}*/
		if(id == account && pw == password) {
			return true;
		}
	}
	return false;
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
void main()
{
	MainMenu();
	system("pause");
}