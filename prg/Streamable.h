/*
Citation and Sources...
Final Project Milestone 2
Module: Streamable
Filename: Streamable.h
Version 1.0
Author	Aung Moe Thwe
Revision History
-----------------------------------------------------------
Date      Reason
2024/7/23  Preliminary release
2024/7/23  Debugged and updated
2024/7/27  Finalised Project
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SENECA_STREAMABLE_H
#define SENECA_STREAMABLE_H

#include <iostream>

namespace sdds {
	class Streamable {
	public:
		virtual std::ostream& write(std::ostream& os)const = 0; 
		virtual std::istream& read(std::istream& is)const = 0;
		virtual bool conIO(std::ios& ios) const = 0;
		virtual operator bool() const=0;

		virtual ~Streamable();
	};

	std::ostream& operator<<(std::ostream& os, const Streamable& s);
	std::istream& operator>>(std::istream& is, const Streamable& s);
}

#endif // !SENECA_STREAMABLE_H
