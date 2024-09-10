/*
Citation and Sources...
Final Project Milestone 4
Module: Book
Filename: Book.cpp
Version 1.0
Author	Aung Moe Thwe
Revision History
-----------------------------------------------------------
Date      Reason
2024/7/27  Preliminary release
2024/7/8   Finalised Project
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Book.h"

#include <cstring>

namespace sdds {
	Book::Book() : m_authorName(nullptr) {}

	Book::Book(const Book& other) : Publication(other), m_authorName(nullptr) {
		*this = other;
	}

	Book& Book::operator=(const Book& other)
	{

		if (this != &other) {
			Publication::operator=(other);
			delete[] m_authorName;
			m_authorName = nullptr;
			if (other.m_authorName != nullptr) {
				m_authorName = new char[strlen(other.m_authorName) + 1];
				strcpy(m_authorName, other.m_authorName);
			}
			else {
				m_authorName = nullptr;
			}
		}
		return *this;


	}

	Book::~Book()
	{
		delete[] m_authorName;
	}

	char Book::type() const
	{
		return 'B';
	}


	std::ostream& Book::write(std::ostream& os) const {
		Publication::write(os);
		if (conIO(os)) {
			os << " ";
			if (m_authorName) {
				int len = strlen(m_authorName);
				os.write(m_authorName, len < SDDS_AUTHOR_WIDTH ? len : SDDS_AUTHOR_WIDTH);
				if (len < SDDS_AUTHOR_WIDTH) {
					os << std::setw(SDDS_AUTHOR_WIDTH - len) << std::setfill(' ') << "";
				}
			}
			else {
				os << std::setw(SDDS_AUTHOR_WIDTH) << std::setfill(' ') << "";
			}
			os << " |";
		}
		else {
			os << '\t' << (m_authorName ? m_authorName : "") << '\n';
		}
		return os;
	}


	std::istream& Book::read(std::istream& is)
	{
		char temp[256]{};

		Publication::read(is);

		if (m_authorName)
		{
			delete[] m_authorName;
			m_authorName = nullptr;
		}

		if (Publication::conIO(is))
		{
			is.ignore();
			std::cout << "Author: ";
			is.getline(temp, 256);
		}
		else
		{
			is.ignore();
			is.get(temp, 256);
		}
		if (!is.fail())
		{
			m_authorName = new char[strlen(temp) + 1];
			strcpy(m_authorName, temp);
		}
		return is;
	}



	void Book::set(int memberId)
	{
		Publication::set(memberId);
		resetDate();
	}

	Book::operator bool() const
	{
		return m_authorName != nullptr && m_authorName[0] != '\0' && Publication::operator bool();
	}

}


