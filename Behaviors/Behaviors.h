#pragma once
#include "UserAccount.h"
#include <string>
#include <vector>
using namespace std;
class OTP;
string bh_mkdir(UserAccount* p);
void _EmailHandle(string cont, string email);
void split(const string& str, const string& delim, vector<string>& parts);
class OTP
{
	string nd;
	time_t o;
public:
	string toString();
	OTP();
	bool isaAuthenticate(string otp);
	string randOTP();
	bool isExpired();
};


class Behaviors
{
protected:
	double value;
	time_t trans;
public:
	OTP otp;
	virtual void saveLog(const char* content, const char* path) = 0;
	virtual void Export(const char* path) = 0;
	virtual string toString() = 0;
	virtual string toScreen() = 0;
	void settime(time_t rha);
	bool sentOTP(string email);
};


class LoginBehavior : public Behaviors
{
public:
	void saveLog(const char* content, const char* path);
	void Export(const char* path);
	string toString();
	string toScreen();
	LoginBehavior();
};

class ChangePWBehavior : public Behaviors
{
public:
	void saveLog(const char* content, const char* path);
	void Export(const char* path);
	string toScreen();
	string toString();
	ChangePWBehavior();
};



class TransferBehavior : public Behaviors
{
public:
	void saveLog(const char* content, const char* path);
	void Export(const char* path);
	string toScreen();
	string toString();
	TransferBehavior(double value);
};

class LinkedToSubAccountBehaviors : public Behaviors
{
public:
	void saveLog(const char* content, const char* path);
	void Export(const char* path);
	string toScreen();

	string toString();
	LinkedToSubAccountBehaviors(double value);
};
bool checkOTP(Behaviors* p);
vector<Behaviors*> ReadData(UserAccount* &p);
//Transaction modified
#include <utility>
#include<exception>
#include<sstream>
#include <memory.h>
class FileNotFoundException : public exception {
private:
	string path;
public:
	explicit FileNotFoundException(string path) {
		this->path = std::move(path);
	}

	const char* what() const noexcept override {
		stringstream stream;
		stream << "Message: File Not Found Exception" << endl;
		stream << "Detail: " << path << " is not a file! " << endl;
		return _strdup(stream.str().c_str());
	}
};

