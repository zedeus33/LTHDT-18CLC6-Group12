#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include<iomanip>
#include <conio.h>
#include "Bank.h"
using namespace std;


//#include "sha1.h"
int chooseInt(int m);
int toInt(string in);
bool isNum(string in);
//bool checkLogin(string& account, string& password, const char* path);
void notice(string sentence, string horizontal, string vertical);
void inputIDPassword(string& id, string& password);
void changePassword(UserAccount*& a);

void MenuSignIn();
void MainMenu();
void UserMenu(UserAccount*& customer);
bool checkLoginAdmin(string& account, string& password, const char* path);
UserAccount* checkLoginUser(string id, string password);
void AdminMenu(string id);

//void MenuUserInfor();
//void MenuTransfer();
//void MenuPayment();
//void MenuDealHistory();
void MenuOthertasks(UserAccount*& customer);
//void MenuAdjustLimit();
//void MenuSaving();
void MenuSignUp();


float InputFloat(float& a, const char* text);
int InputInt(int& a, const char* text);
bool InputBool(bool& a, const char* text);

void MainMenuContinue();
void MenuOtherTasksContinue(UserAccount*& cus);