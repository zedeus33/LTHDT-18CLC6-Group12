#define _CRT_SECURE_NO_WARNINGS
#include "Behaviors.h"
#include "UserAccount.h"
#define lenOTP 6
#include <ctime>
#include <fstream>
#include <iostream>
#include "Function_Sup.h"
using namespace std;
#define ATFILE "./ATTACHMENT.FILE"
#define DATA_BEHAVIORS "D:/TalangBanking/Data/Behaviors/"
#include <string>
#include <windows.h>


//Delete this function when merge code

void split(const string& str, const string& delim, vector<string>& parts) {
	size_t start, end = 0;
	while (end < str.size()) {
		start = end;
		while (start < str.size() && (delim.find(str[start]) != string::npos)) {
			start++;  // skip initial whitespace
		}
		end = start;
		while (end < str.size() && (delim.find(str[end]) == string::npos)) {
			end++; // skip to end of word
		}
		if (end - start != 0) {  // just ignore zero-length strings.
			parts.push_back(string(str, start, end - start));
		}
	}
}

vector<Behaviors*> ReadData(UserAccount*&p)
{
	ifstream fin;
	fin.open(bh_mkdir(p).c_str(),ios_base::in);
	if (!fin.is_open())
		throw FileNotFoundException(bh_mkdir(p));
	vector <Behaviors*> bh;
	while (!fin.eof())
	{
		Behaviors* p = nullptr;
		vector<string> arguments;
		string temp;
		getline(fin, temp);
		if (temp == "")
			return bh;
		split(temp.c_str(), ",", arguments);
		if (arguments[0] == "Login behavior")
		{
			p = new LoginBehavior();
		}
		else if (arguments[0] == "Change Password")
		{
			p = new ChangePWBehavior();
		}
		else if (arguments[0] == "Transfer")
		{
			p = new TransferBehavior(toDouble(arguments[2]));
		}
		else
		{
			p = new LinkedToSubAccountBehaviors(toDouble(arguments[2]));
		}
		p->settime(toDouble(arguments[1]));
		bh.push_back(p);
	}
	return bh;
}



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
		srand(time(0));
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
	if (!fout.is_open())
		throw FileNotFoundException(path);
	fout << content;
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
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	fout << is.str();
	fout.close();

}

string LoginBehavior::toString()
{
	stringstream is;
	is << "Login behavior," << this->trans << "," << this->value << endl;
	return is.str().c_str();
}

string LoginBehavior::toScreen()
{
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "User Login" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	return is.str();
}

LoginBehavior::LoginBehavior()
{
	value = 0;
	trans = time(0);
}

void Behaviors::settime(time_t rha)
{
	this->trans = rha;
}

bool Behaviors::sentOTP(string email)
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

bool checkOTP(Behaviors* p)
{
	string inOTP;
	cout << "Please enter your otp we have sent to your email: ";
	cin >> inOTP;
	if (p->otp.isaAuthenticate(inOTP))
		return true;
	return false;
}

void ChangePWBehavior::saveLog(const char* content, const char* path)
{
	ofstream fout;
	fout.open(path, std::ios_base::app);
	if (!fout.is_open())
		throw FileNotFoundException(path);
	fout << content;
	fout.close();
}

void ChangePWBehavior::Export(const char* path)
{
	ofstream fout;
	fout.open(path, ios_base::app);
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "Change Password" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	fout << is.str();
	fout.close();
}

string ChangePWBehavior::toScreen()
{
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "Change Password" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	return is.str();
}

string ChangePWBehavior::toString()
{
	stringstream is;
	is << "Change Password," << this->trans << "," << this->value << endl;
	return is.str().c_str();
}

ChangePWBehavior::ChangePWBehavior()
{
	value = 0;
	trans = time(0);
}

void TransferBehavior::saveLog(const char* content, const char* path)
{
	ofstream fout;
	fout.open(path, std::ios_base::app);
	if (!fout.is_open())
		throw FileNotFoundException(path);
	fout << content;
	fout.close();
}

void TransferBehavior::Export(const char* path)
{
	ofstream fout;
	fout.open(path, ios_base::app);
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "Transfer" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	fout << is.str();
	fout.close();
}

string TransferBehavior::toScreen()
{
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "Transfer" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	return is.str();
}

string TransferBehavior::toString()
{
	stringstream is;
	is << "Transfer," << this->trans << "," << this->value << endl;
	return is.str().c_str();
}

TransferBehavior::TransferBehavior(double value)
{
	this->trans = time(0);
	this->value = value;
}

string bh_mkdir(UserAccount* p)
{
	stringstream is;
	is << string(DATA_BEHAVIORS) << p->getUsername() << ".txt";
	return is.str();
}

void LinkedToSubAccountBehaviors::saveLog(const char* content, const char* path)
{
	ofstream fout;
	fout.open(path, std::ios_base::app);
	if (!fout.is_open())
		throw FileNotFoundException(path);
	fout << content;
	fout.close();
}

void LinkedToSubAccountBehaviors::Export(const char* path)
{
	ofstream fout;
	fout.open(path, ios_base::app);
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "Link to subaccount" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	fout << is.str();
	fout.close();
}

string LinkedToSubAccountBehaviors::toScreen()
{
	stringstream is;
	tm* t = localtime(&this->trans);
	is << "Link to subaccount" << ",";
	is << t->tm_mday << '/' << t->tm_mon + 1 << '/' << t->tm_year + 1900 << ',';
	is << t->tm_hour << ':' << t->tm_min << ':' << t->tm_sec << ",";
	is << value << endl;
	return is.str();
}

string LinkedToSubAccountBehaviors::toString()
{
	stringstream is;
	is << "Linked Behavior," << this->trans << "," << this->value << endl;
	return is.str().c_str();
}

LinkedToSubAccountBehaviors::LinkedToSubAccountBehaviors(double value)
{
	value = 0;
	trans = time(0);
}
