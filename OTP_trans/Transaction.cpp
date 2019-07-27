#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#define lenOTP 21
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
#define ATFILE "./ATTACHMENT.FILE"
#include <string>
#include <windows.h>

string OTP::toString()
{
	return nd;
}

OTP::OTP()
{
	this->randOTP();
}
bool OTP::isaAuthenticate(string otp)
{
	if (!this->isExpired())
		return false;
	
	return (this->nd == otp);
}
string OTP::randOTP()
{
		// All possible characters of my OTP 
		string str = "abcdefghijklmnopqrstuvwxyzABCD"
			"EFGHIJKLMNOPQRSTUVWXYZ0123456789";
		int n = str.length();

		// String to hold my OTP 
		for (int i = 1; i <= lenOTP; i++)
			nd.push_back(str[rand() % n]);
		o = time(0);
		return(nd);
}

bool OTP::isExpired()
{
	time_t t = time(0);
	double dif = difftime(t,o) / (60);
	if (abs(dif) < 5)
		return true;
	return false;
}

void LoginBehavior::saveLog(const char* content, const char* path)
{
	ofstream fout;
	fout.open(path,std::ios_base::app);
	if (fout.is_open())
		throw FileNotFoundException(path);
	fout << content << endl;
	fout.close();

}

void LoginBehavior::Export(const char* path)
{
	ofstream fout;
	fout.open(path,ios_base::app);
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "User Login" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << endl;
	fout << is.str();
	fout.close();

}

string LoginBehavior::toString()
{
	stringstream is;
	is << "Login behavior," << this->trans << "," << this->value << endl;
	return is.str().c_str();
}

LoginBehavior::LoginBehavior()
{
	value = 0;
	trans = time(0);
}

bool LoginBehavior::sentOTP(string email)
{
	stringstream cont;
	cont <<  "Your otp code is " << this->otp.toString() << endl;
	cont << "This otp will experied in 5 minutes." << endl;
	_EmailHandle(cont.str(), email);
	return false;
}

void _EmailHandle(string cont, string email)
{
	string command = "curl -s -o nul -v --output \"/dev/null\" smtp://smtp.gmail.com:587 -v --mail-from \"task.toandoan@gmail.com\" --mail-rcpt " + email + " --ssl -u task.toandoan@gmail.com:142857Toan! -T " + string(ATFILE) + " -k --anyauth";
	ofstream fout;
	fout.open((ATFILE));
	fout << cont;
	fout.close();
	system(command.c_str());
	system("cls");
	cout << "A OTP has been sent to your mail at: " << email << endl;
	cout << "OTP will expired in 5 minutes" << endl;
}

bool checkOTP(Transaction* p)
{
	string inOTP;
	cout << "Please enter your otp we have sent to your email: ";
	cin >> inOTP;
	if (p->otp.isaAuthenticate(inOTP))
		return true;
	return false;
}