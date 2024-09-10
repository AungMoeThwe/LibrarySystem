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


#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "Publication.h"
#include "Lib.h"
#include"Date.h"


namespace sdds {
	class Book: public Publication {
		char* m_authorName;

	public:
		
		//Constructors
		Book();
		Book(const Book& other);
		Book& operator=(const Book& other);
		virtual ~Book();

		//Type Method
		char type() const override;

		//Read and Write Methods
		std::istream& read(std::istream& is) override;
		std::ostream& write(std::ostream& os) const override;

		//Set Method
		void set(int memberId) override;
		operator bool() const override;



	};
}

#endif // !SENECA_BOOK_H



