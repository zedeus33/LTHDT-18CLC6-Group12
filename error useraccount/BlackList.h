#pragma once
#include "string"
#include "iostream"
#include "vector"
using namespace std;
class BlackList
{
public:
	BlackList();
	void setBlackList(vector <string> &x);
	bool addToBlaskList(string numID);
	bool isBlock(string numID);
	~BlackList();

private:
	vector <string> numID;
};