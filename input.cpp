#include <iostream>
#include <string>
#include <cstring>

using namespace std;

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

