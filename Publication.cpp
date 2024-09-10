/*
Citation and Sources...
Final Project Milestone 2
Module: Publication
Filename: Publication.cpp
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
#include <cstring>

#include "Publication.h"
#include "Lib.h"


namespace sdds {
	Publication::Publication()
	{
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		resetDate();
	}

	//Modifiers

	void Publication::set(int member_id)
	{
		m_membership = member_id;
	
	}

	void Publication::setRef(int value)
	{
		m_libRef = value;
	}

	void Publication::resetDate()
	{
		m_date = Date();
	}

	//Queries
	char Publication::type() const
	{
		return 'P';
	}

	bool Publication::onLoan() const
	{

		return (m_membership != 0);
	}

	Date Publication::checkoutDate() const
	{
		return m_date;
	}

	bool Publication::operator==(const char* title) const
	{
		return strstr(m_title, title) != nullptr;
	}

	Publication::operator const char* () const
	{
		return m_title;
	}

	int Publication::getRef() const
	{
		return m_libRef;
	}

	int Publication::getMemID() const
	{
		return m_membership;
	}

	//Overrides
	bool Publication::conIO(std::ios& io) const
	{
		return &io == &std::cin || &io == &std::cout;
	}

	std::ostream& Publication::write(std::ostream& os) const
	{

		char temp[SDDS_TITLE_WIDTH + 1]{ 0 };
		std::strncpy(temp, m_title, SDDS_TITLE_WIDTH);

		if (conIO(os)) // LEFT JUSTIFIED WITH DOTS
		{
			os << "| " << m_shelfId << " | " << std::setw(SDDS_TITLE_WIDTH) << std::left <<
				std::setfill('.') << temp << " | ";
			(m_membership != 0) ? os << m_membership : os << " N/A ";
			os << " | " << m_date << " |";
		}
		else { // File I/O
			os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
			(m_membership != 0) ? os << m_membership : os << "0";
			os << "\t" << m_date;
			if (type() == 'P')
			{
				os << "\n";
			}

		}
		return os;

	}	


	std::istream& Publication::read(std::istream& istr) {
		char title[256]{};
		char shelfId[SDDS_SHELF_ID_LEN + 1]{};
		int libRef = -1, memberShip = 0;
		Date n_date;

		if (m_title) {
			delete[] m_title;
			m_title = nullptr;
		}
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		resetDate();

		if (conIO(istr)) {
			std::cout << "Shelf No: ";
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1);
			if (strlen(shelfId) != SDDS_SHELF_ID_LEN) {
				istr.setstate(std::ios::failbit);
			}
			std::cout << "Title: ";
			istr.getline(title, 256);
			std::cout << "Date: ";
			
		}
		else {
			istr >> libRef;
			istr.ignore();
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.getline(title, 256, '\t');
			istr >> memberShip;
			istr.ignore();
			
		}

		istr >> n_date;

		if (!n_date) {
			istr.setstate(std::ios::failbit);
		}
		if (istr) {
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
			strcpy(m_shelfId, shelfId);
			m_membership = memberShip;
			m_date = n_date;
			m_libRef = libRef;
		}
		return istr;
	}


	Publication::operator bool() const
	{
		return m_title != nullptr && m_shelfId[0] != '\0';
	}


	// RULE OF THREE
	Publication::Publication(const Publication& p)
	{

		*this = p;
	}

	Publication& Publication::operator=(const Publication& p)
	{
		if (this != &p) {
			set(p.m_membership);
			setRef(p.m_libRef);
			strcpy(m_shelfId, p.m_shelfId);
			m_date = p.m_date;
			if (m_title) {
				delete[] m_title;
				m_title = nullptr;
			}
			if (p.m_title != nullptr) {
				m_title = new char[strlen(p.m_title) + 1];
				strcpy(m_title, p.m_title);
			}
			else {
				m_title = nullptr;
			}
		}
		return *this;
	}

	Publication::~Publication()
	{
		delete[] m_title;
	}


	std::ostream& operator<<(std::ostream& os, const Publication& p)
	{
		if (p)
		{
			p.write(os);
		}
		return os;
	}

	std::istream& operator>>(std::istream& is, Publication& p)
	{
		return p.read(is);
	}

}

