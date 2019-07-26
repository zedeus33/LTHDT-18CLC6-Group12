#pragma once
#include "iostream"
#include "string"
#include "fstream"
using namespace std;
template <class T>
bool addFile(const char * path, T content, string endline = "")
{
	ofstream fout;
	fout.open(path, ios::app);
	if (fout.is_open() == true)
	{
		fout << content << endline;
		fout.close();
		return true;
	}
	else
	{
		return false;
	}
}
