#include "BlackList.h"

BlackList::BlackList()
{

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