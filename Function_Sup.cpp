#include "Function_Sup.h"

void notice(string sentence,string horizontal = "=",string vertical = "=")
{
	cout << setw(90);
	for (int i = 0; i < ((sentence.size() + 4) /horizontal.size()); i++)
	{
		cout << horizontal;
	}
	if (horizontal.size()==2 && sentence.size()%2!=0)
	{
		cout << horizontal[0];
	}
	cout << "\n";
	if (horizontal.size() == 2)
	{
		cout << setw(89);
	}
	else
	{
		cout << setw(90);
	}
	cout << vertical << " " << sentence << " " << vertical << "\n";
	cout << setw(90);
	for (int i = 0; i < ((sentence.size() + 4) / horizontal.size()); i++)
	{
		cout << horizontal;
	}
	if (horizontal.size() == 2 && sentence.size() % 2 != 0)
	{
		cout << horizontal[0];
	}
	cout << "\n";
}
