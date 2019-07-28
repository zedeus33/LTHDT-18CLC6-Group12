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
bool changePassword(UserAccount*& a);
bool checkLoginAdmin(string& account, string& password, const char* path);
UserAccount* checkLoginUser(string id, string password);

void MenuSignIn();
void MainMenu();
void UserMenu(UserAccount*& customer);

void AdminMenu(string id);

//void MenuUserInfor();
//void MenuTransfer();
//void MenuPayment();
//void MenuDealHistory();
void MenuOthertasks(UserAccount*& customer);
//void MenuAdjustLimit();
//void MenuSaving();
void MenuSignUp();

void MainMenuContinue();
void MenuOtherTasksContinue(UserAccount*& cus);

bool alnum(string s);
void checkSocialID(const string& id);
void checkEmail(const string& email);
string inputSocialID(string SocialID, const char* text);
string inputEmail(string Email, const char* text);
float InputFloat(float& a, const char* text);
int InputInt(int& a, const char* text);
bool InputBool(bool& a, const char* text);
bool checkStringExist(vector <string> x, string y);
string fun_randomChar(int amount);
string createDefaultUserID();
string createDefaultNumID();