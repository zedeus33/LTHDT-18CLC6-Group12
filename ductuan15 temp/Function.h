#pragma once
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

bool alnum(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return 0;
		}
	}
	return 1;
}

void checkSocialID(const string& id)
{
	if (id.length() != 9)
	{
		throw "Length ERROR";
	}
	if (alnum(id) == 0)
	{
		throw "Type ERROR \n Type Expected: NUMBER";
	}
}

void checkEmail(const string& email)
{
	for (int i = 0; i < email.length(); i++)
	{
		if (email[i] == '@')
		{
			if (i == 0)
			{
				throw "Invalid Email!!Please try again~";
			}
			else
			{
				return;
			}
		}

	}
	throw "Invalid Email!!Please try again~";

}

string inputSocialID(string SocialID, const char* text)
{
	do
	{
		cout << text;
		getline(cin, SocialID, '\n');
		try
		{
			checkSocialID(SocialID);
			break;
		}
		catch(const char* error)
		{
			cout << error << endl;
		}
	} while (true);
	return SocialID;
}

string inputEmail(string Email, const char* text)
{
	do
	{
		cout << text;
		getline(cin, Email, '\n');
		try
		{
			checkEmail(Email);
			break;
		}
		catch(const char* error)
		{
			cout << error << endl;
		}
	} while (true);
	return Email;
}

float InputFloat(float& a, const char* text)
{
	bool check;
	float  temp;
	do
	{
		stringstream iss;
		string sInput;
		cout << text;
		getline(cin, sInput, '\n');
		iss << sInput;
		iss >> temp;
		check = iss.eof() && !iss.fail();
		if (check == 0)
		{
			cout << "WRONG TYPE__TYPE EXPECTED: NUMBER" << endl;
			cout << "Please try again!" << endl;
			continue;
		}
		else
		{
			a = temp;
			return a;
		}
	} while (true);
}

int InputInt(int& a, const char* text)
{
	int temp;
	bool check;
	do
	{
		string sInput;
		stringstream iss;
		cout << text;
		getline(cin, sInput, '\n');
		iss << sInput;
		iss >> temp;
		check = iss.eof() && !iss.fail();
		if (check == 0)
		{
			cout << "WRONG TYPE__TYPE EXPECTED: NUMBER" << endl;
			cout << "Please try again!" << endl;
			continue;
		}
		else
		{
			a = temp;
			return a;
		}
	} while (true);
}

bool InputBool(bool& a, const char* text)
{
	bool temp;
	bool check;
	do
	{
		string sInput;
		cout << text;
		getline(cin, sInput, '\n');
		if (sInput == "0")
		{
			temp = 0;
			a = temp;
			return temp;
		}
		else if (sInput == "1")
		{
			temp = 1;
			return a;
		}
		else
		{
			cout << "WRONG TYPE__TYPE EXPECTED: BOOL" << endl;
			cout << "Please try again!" << endl;
		}
	} while (true);
}