#pragma once
#include "iostream"
#include "string"
#include "fstream"
using namespace std;
bool checkFileExist(const char *path);
string read(const char *path, int pos_begin, int pos_end);
string readline(const char *path, int line);
void copyBinary(const char *from, const char *to);

bool checkFileExist(const char * path)
{
	fstream file;
	file.open(path);
	if (file.is_open() == true)
	{
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

string read(const char * path, int pos_begin, int pos_end)
{
	ifstream fin;
	fin.open(path);
	if (fin.is_open() == true)
	{
		fin.seekg(pos_begin);
		char x;
		string temp;
		for (int i = 0; i < pos_end - pos_begin; i++)
		{
			fin >> x;
			temp = temp + x;
		}
		return temp;
	}
	else
	{
		return "Can't open file\n";
	}
}

string readline(const char * path, int line)
{
	ifstream fin;
	fin.open(path);
	if (fin.is_open() == true)
	{
		int i = 1;
		string temp;
		while (fin.eof() == false)
		{
			getline(fin, temp, '\n');
			if (temp == "")
			{
				continue;
			}
			if (line == i)
			{
				fin.close();
				return temp;
			}
			i++;
		}
		fin.close();
		return "This line doesn't exist!\n";
	}
	else
	{
		return "Can't open file\n";
	}
}

void copyBinary(const char * from, const char * to)
{
	ifstream source;
	ofstream dest;
	source.open(from, ios::binary);
	source.open(to, ios::binary);
	istreambuf_iterator <char> begin_source(source);
	istreambuf_iterator <char> end_source;
	ostreambuf_iterator <char> begin_dest(dest);
	copy(begin_source, end_source, begin_dest);
	source.close();
	dest.close();
}


