#pragma once
#pragma once
#include "string"
#include "iostream"
#include "vector"
using namespace std;
class BlackList
{
private:
	BlackList();
	static BlackList* instance;
public:
	static BlackList* getBlackList();
	void setBlackList(vector <string>& x);
	bool addToBlaskList(string numID);
	bool removeFromBlackList(string _num);
	bool isBlock(string numID);
	~BlackList();
	bool loadBlackList(const char* path);
	bool saveBlackList(const char* path);
	static void clear();
private:
	vector <string> numID;
};