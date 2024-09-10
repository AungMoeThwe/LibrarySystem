/*
Citation and Sources...
Final Project Milestone 2
Module: Publication
Filename: Publication.h
Version 1.0
Author	Aung Moe Thwe
Revision History
-----------------------------------------------------------
Date      Reason
2024/7/23  Preliminary release
2024/7/27  Debugged
2024/7/27  Finalised Project
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SENECA_PUBLICATION_H
#define SENECA_PUBLICATION_H

#include "Date.h"
#include "Lib.h"
#include "Streamable.h"

namespace sdds {
	class Publication {
		char* m_title;
		char m_shelfId[SDDS_SHELF_ID_LEN + 1]
		{};
		int m_membership; //This attribute is an integer to hold a 5-digit membership number of members of the library.
		int m_libRef; //This serial number is used internally to uniquely identify each publication in the system
		Date m_date;
	public:
		Publication();

		//MODIFIERS MS3
		virtual void set(int member_id);
		// Sets the membership attribute to either zero or a five-digit integer.
		void setRef(int value);
		// Sets the **libRef** attribute value
		void resetDate();
		// Sets the date to the current date of the system.

		//QUERIES MS3
		virtual char type()const;
		//Returns the character 'P' to identify this object as a "Publication object"
		bool onLoan()const;
		//Returns true is the publication is checkout (membership is non-zero)
		Date checkoutDate()const;
		//Returns the date attribute
		bool operator==(const char* title)const;
		//Returns true if the argument title appears anywhere in the title of the 
		//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		operator const char* ()const;
		//Returns the title attribute
		int getRef()const;
		//Returns the libRef attirbute. 
		int getMemID() const;

		//OVERRIDE
		bool conIO(std::ios& io)const;
		virtual std::ostream& write(std::ostream& os) const;
		virtual std::istream& read(std::istream& istr);
		virtual operator bool() const;

		//Rule Of Three
		Publication(const Publication& p);
		Publication& operator=(const Publication& p);
		virtual ~Publication();
	};

	std::ostream& operator<<(std::ostream& os, const Publication& p);
	std::istream& operator>>(std::istream& is, Publication& p);
}



#endif // !SENECA_PUBLICATION_H
