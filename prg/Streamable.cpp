/*
Citation and Sources...
Final Project Milestone 2
Module: Streamable
Filename: Streamable.cpp
Version 1.0
Author	Aung Moe Thwe
Revision History
-----------------------------------------------------------
Date      Reason
2024/7/23  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#include "Streamable.h"

namespace sdds {

	Streamable::~Streamable() {};

	std::ostream& operator<<(std::ostream& os, const Streamable& s)
	{
		if (s)
		{
			s.write(os);
		}
		return os;
	}
	std::istream& operator>>(std::istream& is, const Streamable& s)
	{
		return s.read(is);
	}
}