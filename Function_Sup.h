#pragma once
#include "iostream"
#include "string"
#include "vector"
#include "iomanip"
using namespace std;

void notice(string sentence,string horizontal, string vertical);
template <class T>
T in(T& a, const char* text)
{
	string b;
	T temp;
	do
	{
		cout << text;
		cin >> b;
		try
		{
			temp = stod(b);
			break;
		}
		catch (exception& error)
		{
			cout << "ERROR:WRONG TYPE\nType expected:" << typeid(a).name() << endl;
			continue;
		}
	} while (1);
	a = T(temp);
	return a;
}