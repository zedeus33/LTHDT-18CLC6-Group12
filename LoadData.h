#pragma once
#pragma warning(disable:4996)
#include "File.h"
#include "conio.h"
#include "sstream"
#include <ctime>
#include <vector>
#include "Client.h"
#include "Bank.h"

const string DATA_BANK = "D:/TaLangBanking/Data/Bank/";
const string DATA_ACCOUNTCLIENT = "D:/TaLangBanking/Data/Client/Account/";
const string DATA_PROFILECLIENT = "D:/TaLangBanking/Data/Client/Profile/";
using namespace std;

Date convertToDate(string x);
Client* loadDataClient(string UserID);
void loadDataBank(vector <Bank*> &bank);
