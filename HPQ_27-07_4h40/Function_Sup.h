#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
#include <conio.h>
#include "sstream"
#include "Bank.h"
using namespace std;


//#include "sha1.h"

//
void notice(string sentence, string horizontal, string vertical);




void inputIDPassword(string& id, string& password);




void MenuSignIn();
int chooseInt(int m);
void MainMenu();
void MenuSignIn();
void UserMenu(UserAccount *&customer);
bool checkLoginAdmin(string& account, string& password, const char* path);
UserAccount* checkLoginUser(string id, string password);
void AdminMenu(string id);
//void MenuUserInfor();
//void MenuTransfer();
//void MenuPayment();
//void MenuDealHistory();
//void MenuOthertasks();
//void MenuAdjustLimit();
//void MenuSaving();