#pragma once
#include <string>
#include <vector>
#include<iomanip>
#include <conio.h>
#include <fstream>
#include <cstring>
#include "Bank.h"
#include "LoadData.h"

//#include "sha1.h"
<<<<<<< HEAD

using namespace std;
template <class T>
T in(T& a, const char* text)
{
	string b;
	T temp;
	do
	{
		cout << text;
		cin >> b;
		try
		{
			temp = stod(b);
			break;
		}
		catch (exception& error)
		{
			cout << "ERROR:WRONG TYPE\nType expected:" << typeid(a).name() << endl;
			continue;
		}
	} while (1);
	a = T(temp);
	return a;
}
void notice(string sentence,string horizontal, string vertical);
=======
//template <class T>
//T in(T& a, const char* text)
//{
//	string b;
//	T temp;
//	do
//	{
//		cout << text;
//		cin >> b;
//		try
//		{
//			temp = stod(b);
//			break;
//		}
//		catch (exception& error)
//		{
//			cout << "ERROR:WRONG TYPE\nType expected:" << typeid(a).name() << endl;
//			continue;
//		}
//	} while (1);
//	a = T(temp);
//	return a;
//}
void notice(string sentence, string horizontal, string vertical);
>>>>>>> bba67beda9529672c4c5f29d06a9e00ccb6c6393
void inputIDPassword(string& id, string& password);
void MenuSignIn();
void secondMenu(string id);
int chooseInt(int m);
void MainMenu();
void MenuSignIn();
void secondMenu(string id);
bool checkLogin(string& account, string& password, const char* path);

void MenuUserInfor();
//void MenuTransfer();
//void MenuPayment();
//void MenuDealHistory();
//void MenuOthertasks();
//void MenuAdjustLimit();
//void MenuSaving();
void MenuBankInfor(); 
