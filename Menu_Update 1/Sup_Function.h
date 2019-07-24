#ifndef Sup_Function
#define Sup_Function
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
#include "sha1.h"
using namespace std;
void inputIDPassword(string& id, string& password);
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

