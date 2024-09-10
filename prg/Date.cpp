 // Final Project Milestone 1 
// Date Module
// File	Date.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name              Date                 Reason
// Aung Moe Thwe    7/5/2024               MS1
// Aung Moe Thwe    8/7/2024               MS5
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
namespace sdds {

    //MS3 global vars
    bool sdds_test = false;
    int sdds_year = 2024;
    int sdds_mon = 12;
    int sdds_day = 25;

   bool Date::validate() {
      errCode(NO_ERROR);
      if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1) {
         errCode(YEAR_ERROR);
      }
      else if (m_mon < 1 || m_mon > 12) {
         errCode(MON_ERROR);
      }
      else if (m_day < 1 || m_day > mdays()) {
         errCode(DAY_ERROR);
      }
      return !bad();
   }
   int Date::mdays()const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }

   int Date::systemYear()const {
       int theYear = sdds_year;
       if (!sdds_test) {
           time_t t = time(NULL);
           tm lt = *localtime(&t);
           theYear = lt.tm_year + 1900;
       }
       return theYear;
   }

   void Date::setToToday() {
       if (sdds_test) {
           m_day = sdds_day;
           m_mon = sdds_mon;
           m_year = sdds_year;
       }
       else {
           time_t t = time(NULL);
           tm lt = *localtime(&t);
           m_day = lt.tm_mday;
           m_mon = lt.tm_mon + 1;
           m_year = lt.tm_year + 1900;
       }
       errCode(NO_ERROR);
   }

   int Date::daysSince0001_1_1()const { // Rata Die day since 0001/01/01 
      int ty = m_year;
      int tm = m_mon;
      if (tm < 3) {
         ty--;
         tm += 12;
      }
      return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }
   Date::Date() :m_CUR_YEAR(systemYear()) {
      setToToday();
   }
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
      m_year = year;
      m_mon = mon;
      m_day = day;
      validate();
   }
   const char* Date::dateStatus()const {
      return DATE_ERROR[errCode()];
   }
   int Date::currentYear()const {
      return m_CUR_YEAR;
   }
   std::istream& Date::read(std::istream& is)
   {
       int y, m, d;
       char ch;
       errCode(NO_ERROR);
       is >> y >> ch >> m >> ch >> d;
       m_year = y;
       m_mon = m;
       m_day = d;
       if (!is.fail())
       {
           validate();
       }
       else
       {
           errCode(CIN_FAILED);
           is.clear();
       }
       return is;
   }

   std::ostream& Date::write(std::ostream& os) const
   {
       if (!bad())
       { //changed this setw and setfill before mday
           os << m_year << "/" << std::setw(2) << std::setfill('0') << std::right << m_mon << "/" << std::setw(2) << std::setfill('0') << m_day;
       }
       else
       {
           os << dateStatus();
       }
       return os;
   }

   bool Date::operator==(const Date& d) const
   {
       if (this->m_year ==d.m_year && this->m_mon == d.m_mon && this->m_day == d.m_day)
       {
           return true;
       }
       return false;
   }

   bool Date::operator!=(const Date& d) const
   {
       return !(*this == d);
   }

   bool Date::operator>=(const Date& d) const
   {
       return (*this > d) || (*this == d);
   }

   bool Date::operator<=(const Date& d) const
   {
       return (*this < d) || (*this == d);
   }

   bool Date::operator<(const Date& d) const
   {

       if (this->m_year != d.m_year) {
           return this->m_year < d.m_year;
       }
       else if (this->m_mon != d.m_mon) {
           return this->m_mon < d.m_mon;
       }
       else {
           return this->m_day < d.m_day;
       }
   }

   bool Date::operator>(const Date& d) const
   {
       if (this->m_year != d.m_year) {
           return this->m_year > d.m_year;
       }
       else if (this->m_mon != d.m_mon) {
           return this->m_mon > d.m_mon;
       }
       else {
           return this->m_day > d.m_day;
       }
   }

   long int Date::operator-(Date i) const
   {
       return (daysSince0001_1_1() - i.daysSince0001_1_1());
   }

   Date::operator bool() const
   {
       return !bad();
   }

   bool Date::extractChar(std::istream& istr, char ch)
   {
       if (istr.peek() == ch)
       {
           istr.get();
           return true;
       }
       else
       {
           errCode(CIN_FAILED);
           istr.setstate(ios::failbit);
           istr.clear();
           istr.ignore(80, '\n');
           return false;
       }
   }


   void Date::errCode(int readErrorCode) {
      m_ErrorCode = readErrorCode;
   }
   int Date::errCode()const {
      return m_ErrorCode;
   }
   bool Date::bad()const {
      return m_ErrorCode != 0;
   }
  
   ostream& operator<<(ostream& os, const Date& RO) {
      return RO.write(os);
   }
   istream& operator>>(istream& is, Date& RO) {
      return RO.read(is);
   }


}
