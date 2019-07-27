#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
#include <conio.h>
#include "sstream"
using namespace std;


//#include "sha1.h"


void notice(string sentence, string horizontal, string vertical);
void inputIDPassword(string& id, string& password);
void MenuSignIn();
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