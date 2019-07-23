#ifndef Sup_Function
#define Sup_Function
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "sha1.h"
using namespace std;
//void inputIDPassword(string& id, string& password) {
//	cout << "\n\n\n" << endl;
//	system("color a");
//	std::cout << "\t\t\tInput ID :       ";
//	cin >> id;
//	std::cout << "\t\t\tInput password : ";
//
//
//	char pass;
//	string temp;
//	do
//	{
//		pass = getch();
//		if (pass == '\n' || pass == '\r')
//		{
//			cout << "\n";
//			break;
//		}
//		else if (pass == '\b')
//		{
//			cout << "\b \b";
//			if (temp.empty() == false)
//			{
//				temp.erase(temp.size() - 1);
//			}
//		}
//		else if (pass == -32)
//		{
//			getch();
//		}
//		else if (isprint(pass) && temp.size() < 10)
//		{
//			cout << "*";
//			temp = temp + pass;
//		}
//	} while (true);
//	password = temp;
//	system("color f");
//}
void MenuSignIn();
void secondMenu(string id);
int chooseInt(int m);
void MainMenu();
void MenuSignIn();
void secondMenu(string id);
bool checkLogin(string& account, string& password, const char* path);
void MenuUserInfor();
void MenuTransfer();
void MenuPayment();
void MenuDealHistory();
void MenuOthertasks();
void MenuAdjustLimit();
void MenuSaving();

#endif // !Sup_Function

