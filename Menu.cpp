/*
Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
Version 2.0
Author	Aung Moe Thwe
Revision History
-----------------------------------------------------------
Date      Reason
2024/7/5  Preliminary release
2024/7/5  Debugged DMA
2024/7/22 Debugged and updated
2024/7/27 Finalised Project
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <cstring>
#include <iostream>

using namespace std;
namespace sdds {

	MenuItem::MenuItem() : m_menuItem(nullptr) {}

	MenuItem::MenuItem(const char* item) { //check this
		if (item!= nullptr && item[0]) {
			m_menuItem = new char[strlen(item) + 1];
			strcpy(m_menuItem, item);
		}
		else {
			m_menuItem = nullptr;
		}
	}

	MenuItem::~MenuItem()
	{
		delete[] m_menuItem;
	}

	MenuItem::operator bool() const //check this
	{
		return m_menuItem != nullptr && m_menuItem[0] != '\0';
	}

	MenuItem::operator const char* () const //this too
	{
		return m_menuItem;
	}

	void MenuItem::display(std::ostream& os) const {
		if (*this) {
			os << m_menuItem;
		}
	}


	Menu::Menu() : m_menuTitle(nullptr), m_numOfMenu(0) { //either this or just menutitle null and noofmenu 0
		for (int i = 0; i < MAX_MENU_ITEMS; ++i) {
			m_items[i] = nullptr;
		}
	}

	Menu::Menu(const char* title) : Menu()
	{
		if (title && title[0] != '\0') {
			m_menuTitle = new char[strlen(title) + 1];
			strcpy(m_menuTitle, title);
		}
	}

	Menu::~Menu() {
		delete[] m_menuTitle;
		for (int i = 0; i < m_numOfMenu; ++i) {
			delete m_items[i];
		}
	}

	int Menu::run()
	{
		display();
		char choice;
		cin >> choice;
		int x = choice - '0';
		while (x < 0 || x > m_numOfMenu)
		{
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Invalid Selection, try again: ";
			cin >> choice;
			x = choice - '0';
		}
		return x;
	}

	void Menu::display()
	{
		if (m_menuTitle != nullptr)
		{
			cout << m_menuTitle << endl; // No need : in ms2 CHECK if need \n or not again!
		}
		for (int i = 0; i < m_numOfMenu; i++)
		{
			cout << " " << i + 1 << "- " << m_items[i]->m_menuItem << endl;
		}
		cout << " 0- Exit\n> ";
	}

	char* Menu::operator[](int i) const
	{
		return m_items[i]->m_menuItem;
	}

	Menu::operator bool() const
	{
		if (m_menuTitle == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	int Menu::operator~() //same as run function but overloaded
	{
		return run();
	}


	std::ostream& Menu::write(std::ostream& os) const
	{
		if (m_menuTitle != nullptr) {
			os << m_menuTitle;
		}
		return os;
	}

	Menu& Menu::operator<<(const char* menuContent)
		{
			if (m_numOfMenu < MAX_MENU_ITEMS) {
			if (menuContent != nullptr && menuContent[0] != '\0') {
				m_items[m_numOfMenu] = new MenuItem(menuContent);
				m_numOfMenu++;
			}
		}
		return *this;
	}


	Menu::operator unsigned int() const
	{
		return m_numOfMenu;
	}




	std::ostream& operator<<(std::ostream& os, const Menu& m)
	{
		return m.write(os);
	}

}