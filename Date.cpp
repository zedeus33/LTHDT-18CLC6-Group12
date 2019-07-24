//
// Created by becut on 5/20/2019.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <ctime>

int Date::s_DayRemain[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
int Date::s_LeafYear_DayRemain[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

Date::Date(int day, int month, int year) {
    m_day = day;
    m_month = month;
    m_year = year;
}

void Date::input() {
    do {
        cout << "Enter day of the date: ";
        cin >> m_day;
        cout << "Enter month of the date: ";
        cin >> m_month;
        cout << "Enter year of the date: ";
        cin >> m_year;
        if (!this->isValid()) {
            cout << "Wrong input!" << endl;
            cout << "Try again " << endl;
        }
    } while (!this->isValid());
    cout << this->output() << endl;
}

//Date::Date()
//{
//	m_day = 1;
//	m_month = 1;
//	m_year = 1900;
//}

int Date::getMDay() const {
    return m_day;
}

void Date::setMDay(int mDay) {
    m_day = mDay;
}

int Date::getMMonth() const {
    return m_month;
}

void Date::setMMonth(int mMonth) {
    m_month = mMonth;
}

int Date::getMYear() const {
    return m_year;
}

void Date::setMYear(int mYear) {
    m_year = mYear;
}

bool Date::isValid() {
    if (m_year <= 0)
        return false;
    if (m_month < 1 || m_month > 12)
        return false;
    if (m_day < 1 || m_day > 31)
        return false;
    if (m_month == 2) {
        if (this->isLeafYear())
            return (m_day <= 29);
        else return (m_day <= 28);
    }
    if (m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)
        return (m_day <= 30);
    return true;
}

bool Date::isLeafYear() {
    return (0 == m_year % 400 || ((m_year % 4 == 0) &&
                                  (m_year % 100 != 0)));
}

string Date::output() {
    string ans;
    stringstream is;
    is << m_day << "/" << m_month << "/" << m_year;
    is >> ans;
    return ans;
}

void Date::increase(int n) {
    for (int i = 0; i < n; i++) {
        this->increase();
    }
}

void Date::increase() {
    if (this->isLastDay()) {
        if (m_month == 12) {
            m_month = 1;
            m_day = 1;
            m_year++;
        } else {
            m_month++;
            m_day = 1;
        }
    } else
        m_day++;
}

void Date::decrease() {
    if (this->isFirstDay()) {
        if (m_month == 1) {
            m_month = 12;
            m_day = 31;
            m_year--;
        } else {
            m_month--;
            m_day = lastDayofMonth();
        }
    }
    m_day--;
}

bool Date::isLastDay() {
    if ((m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10 ||
         m_month == 12) && m_day == 31)
        return true;
    else if (m_month == 2) {
        if (this->isLeafYear())
            return (m_day == 28);
        else
            return (m_day == 29);
    } else
        return (m_day == 30);
}

Date::Date(const Date &p) {
    this->m_day = p.m_day;
    this->m_month = p.m_month;
    this->m_year = p.m_year;
}

void Date::decrease(int n) {
    for (int i = 0; i < n; i++)
        this->decrease();
}

bool Date::isFirstDay() {
    return (m_day == 1);
}

int Date::lastDayofMonth() {
    if (m_month == 2) {
        if (this->isLeafYear())
            return 29;
        return 28;
    }
    if (m_month == 4 || m_month == 5 || m_month == 9 || m_month == 11)
        return 30;
    return 31;
}

int Date::compare(const Date p) {
    if (m_year == p.m_year) {
        if (m_month == p.m_month) {
            if (m_day == p.m_day) {
                return 0;
            } else
                return (m_day > p.m_day ? 1 : -1);
        } else
            return (m_month > p.m_month ? 1 : -1);
    } else
        return (m_year > p.m_year ? 1 : -1);
}

int Date::diff(Date p) {
int i = this->diffFrom111();
int j = p.diffFrom111();
int res = (i-j);
return res;
}

int Date::getRemainDay() {
    int ans;
    if (this->isLeafYear())
        ans = Date::s_LeafYear_DayRemain[this->m_month - 1] + this->m_day;
    else {
        ans = Date::s_DayRemain[this->m_month - 1] + this->m_day;
    }
    return ans;
}

int Date::diffFrom111() {
    int countLeafYear = (m_year - 1) / 4 - (m_year - 1) / 100 + (m_year - 1) / 400;
    int dayRemain = this->getRemainDay();
    return ((m_year - 1) * 365 + countLeafYear + dayRemain - 1);
}

Date::~Date()
{
    m_day = 0;
    m_month = 0;
    m_year = 0;
}


int Date::calcAge() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    Date nw;
    nw.m_day = now->tm_mday;
    nw.m_month = now->tm_mon+1;
    nw.m_year = now->tm_year + 1900;
    int res = abs(this->diff(nw));
    int age = res/365;
    return age;
}

