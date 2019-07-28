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

// Noctice for error
void notice(string sentence, string horizontal, string vertical);


// Create Default Detail For Client
bool checkStringExist(vector <string> x,string y);
string fun_randomChar(int amount);
string createDefaultUserID();
string createDefaultNumID();

// Function of Customer
bool isDouble(string in);
double toDouble(string);
UserAccount* findUserAccount(string numID);
void transfer(UserAccount* &customer);

// Function of Admin


// Function Support For Menu
void inputIDPassword(string& id, string& password);
int chooseInt(int m);
bool checkLoginAdmin(string& account, string& password, const char* path);
UserAccount* checkLoginUser(string id, string password);

// Menu
void MenuSignIn();

void MainMenu();
void MenuSignIn();
void UserMenu(UserAccount *&customer);
void AdminMenu(string id);
//void MenuUserInfor();
//void MenuTransfer();
//void MenuPayment();
//void MenuDealHistory();
//void MenuOthertasks();
//void MenuAdjustLimit();
//void MenuSaving();