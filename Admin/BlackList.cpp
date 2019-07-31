#include "BlackList.h"
#include <fstream>
const string BLACK_LIST = "D:\TaLangBanking\Data\BlackList\BlackList.txt";


BlackList::BlackList()
{

}

BlackList* BlackList::getBlackList()
{
	if (BlackList::instance == nullptr)
	{
		BlackList::instance = new BlackList();
	}
	return BlackList::instance;
}

void BlackList::setBlackList(vector<string>& x)
{
	numID.swap(x);
}

bool BlackList::addToBlaskList(string numID)
{
	if (this->isBlock(numID) == true)
	{
		return false;
	}
	this->numID.push_back(numID);
	return true;
}

bool BlackList::removeFromBlackList(string _num)
{
	std::vector<string>::iterator position = std::find(numID.begin(), numID.end(), _num);
	if (position != numID.end())
		numID.erase(position);
	else
		return false;
	return true;
}

bool BlackList::isBlock(string numID)
{
	for (int i = 0; i < this->numID.size(); i++)
	{
		if (this->numID[i] == numID)
		{
			return true;
		}
	}
	return false;
}

BlackList::~BlackList()
{
	numID.clear();
}

bool BlackList::loadBlackList(const char* path)
{
		ifstream fin(BLACK_LIST, ios_base::in);
		while (!fin.eof())
		{
			string temp;
			getline(fin, temp);
			if (temp == "")
				return true;
			numID.push_back(temp);
		}
		fin.close();
		return true;
}

bool BlackList::saveBlackList(const char* path)
{
	ofstream fout(BLACK_LIST, ios_base::out);
	for (auto &i: this->numID)
	{
		fout << i << endl;
	}
	fout.close();
	return true;
}
