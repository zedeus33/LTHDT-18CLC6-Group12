//
// Created by becut on 5/20/2019.
//

#ifndef ASSIGNMENT01_DATE_H
#define ASSIGNMENT01_DATE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Date {
private:
	int m_day;
	int m_month;
	int m_year;
public:
	//Setter & getter are auto implement by IDE :>
	static int s_DayRemain[12];
	static int s_LeafYear_DayRemain[12];


	int getMDay() const;

	void setMDay(int mDay);

	int getMMonth() const;

	void setMMonth(int mMonth);

	int getMYear() const;

	void setMYear(int mYear);


public:
	explicit Date(int day = 0, int month = 0, int year = 0);

	Date(const Date &p);

	void input();

	string output();

	bool isValid();

	bool isLeafYear();

	void increase(int n);

	void decrease(int n);

	void increase();

	void decrease();

	int compare(const Date p);

	int diffFrom111();
	int diff(Date p = Date(1, 1, 0));

	int getRemainDay();

	int calcAge();

	~Date();

private:
	bool isLastDay();

	bool isFirstDay();

	int lastDayofMonth();
};


#endif //ASSIGNMENT01_DATE_H

