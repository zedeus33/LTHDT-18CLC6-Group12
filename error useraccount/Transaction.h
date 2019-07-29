#pragma once
#include <string>
#include <vector>
using namespace std;
enum Behavior { None,Login, ChangePW, Deposit, Withdraw, Transfer };
class OTP;

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


class Transaction
{
protected:
	float value;
	time_t trans;
public:
	OTP otp;
	virtual void saveLog(const char *content,const char *path) = 0;
	virtual void Export(const char *path) = 0;
	virtual string toString() = 0;
	virtual bool sentOTP(string inOTP) = 0;
};


class LoginBehavior : public Transaction
{
public:
	void saveLog(const char* content, const char* path);
	void Export(const char* path);
	string toString();
	LoginBehavior();
	bool sentOTP(string email);
};
  

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

bool checkOTP(Transaction*& p);