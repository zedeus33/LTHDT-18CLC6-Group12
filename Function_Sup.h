#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
#include <conio.h>
#include <fstream>
#include <cstring>
//#include "sha1.h"
using namespace std;
template <class T>
T in(T& a, const char* text);
void notice(string sentence,string horizontal, string vertical);
void inputIDPassword(string& id, string& password);
void MenuSignIn();
void secondMenu(string id);
int chooseInt(int m);
void MainMenu();
void MenuSignIn();
void secondMenu(string id);
bool checkLogin(string& account, string& password, const char* path);
//void MenuUserInfor();
//void MenuTransfer();
//void MenuPayment();
//void MenuDealHistory();
//void MenuOthertasks();
//void MenuAdjustLimit();
//void MenuSaving();