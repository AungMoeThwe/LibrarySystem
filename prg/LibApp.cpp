/*
Citation and Sources...
Final Project Milestone 2
Module: LibApp
Filename: LibApp.cpp
Version 1.0
Author	Aung Moe Thwe
Revision History
-----------------------------------------------------------
Date      Reason
2024/7/22  Preliminary release
2024/7/8   Finalised Project
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Menu.h"
#include "LibApp.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"


namespace sdds {

	void LibApp::newPublication() {
		if (m_noOfLoadedPubs == SDDS_LIBRARY_CAPACITY) {
			std::cout << "Library is at its maximum capacity!" << std::endl<<std::endl;
		}
		else {
			std::cout << "Adding new publication to the library" << std::endl;

			int pubtype = m_pubMenu.run();
			std::cin.ignore(); // To clear any leftover newlines in the input buffer
			Publication* newTemp = nullptr;

			if (pubtype == 1) {
				newTemp = new Book();
			}
			else if (pubtype == 2) {
				newTemp = new Publication();
			}
			else {
				std::cout << "Aborted!" <<std::endl<< std::endl;
				return;
			}

			std::cin >> *newTemp;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Aborted!" << std::endl;
				delete newTemp;
				return;
			}

			if (confirm("Add this publication to the library?")) {
				if (newTemp) {
					m_lastLibraryRefNum++;
					newTemp->setRef(m_lastLibraryRefNum);
					records[m_noOfLoadedPubs++] = newTemp;
					m_changed = true;
					std::cout << "Publication added\n" << std::endl;
				}
				else {
					std::cout << "Failed to add publication!" << std::endl;
					delete newTemp;
				}
			}
			else {
				std::cout << "Aborted!" <<std::endl<< std::endl;
				delete newTemp;
			}
		}
	}



	void LibApp::removePublication() //MS5 addition
	{
		std::cout << "Removing publication from the library" << std::endl;
		int libRefNum = search();
		if (libRefNum != 0 && confirm("Remove this publication from the library?"))
		{
			getPub(libRefNum)->setRef(0);
			m_changed = true;
			std::cout << "Publication removed" <<std::endl << std::endl;
		}
	}

	void LibApp::checkOutPub() //MS5 addition 
	{
		std::cout<< "Checkout publication from the library" << std::endl;

		int num;
		int libRefNum = search(0);
		if (libRefNum == 0) {
			return;
		} 

		if (confirm("Check out publication?")) {
			std::cout << "Enter Membership number: ";
			std::cin >> num;
			while (num > 99999 || num < 10000)
			{
				std::cout << "Invalid membership number, try again: ";
				std::cin >> num;
			}
			getPub(libRefNum)->set(num);
			m_changed = true;
			std::cout << "Publication checked out" << std::endl << std::endl;
		}
	}


	LibApp::LibApp(const char* filename) : 
		m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		m_pubMenu("Choose the type of publication:") {
		strcpy(m_filename, filename);
		m_changed = false;
		m_noOfLoadedPubs = 0;
		m_lastLibraryRefNum = 0;
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_pubMenu << "Book" << "Publication";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		
		load();
	}

	void LibApp::run()
	{
		bool done = false;
		while (!done) {
			switch (m_mainMenu.run()) {
			case 1:
				newPublication();
				break;
			case 2:
				removePublication();
				break;
			case 3:
				checkOutPub();
				break;
			case 4:
				returnPub();
				break;
			case 0:
				if (m_changed) {
					switch (m_exitMenu.run()) {
					case 0:
						if (confirm("This will discard all the changes are you sure?")) {
							done = true;

						}
						break;
					case 1:
						save();
						done = true;
						break;
					
					case 2:
						std::cout << std::endl;
					}

				}
				else {
					done = true;
				}
				break;
			}
		}
		std::cout << "\n-------------------------------------------" << std::endl;
		std::cout << "Thanks for using Seneca Library Application" << std::endl;
	}

	bool LibApp::confirm(const char* message)
	{
		Menu menu(message);
		menu << "Yes";
		return menu.run() == 1;
	}

	void LibApp::load() {

		std::cout << "Loading Data" << std::endl;
		std::ifstream infile(m_filename);
		char type = {};

		for (int i = 0; infile; i++) {
			infile >> type;
			infile.ignore();

			if (infile) {

				if (type == 'P') {
					records[i] = new Publication;
				}
				else if (type == 'B') {
					records[i] = new Book;
				}

				if (records[i]) {
					infile >> *records[i];
					m_lastLibraryRefNum = records[i]->getRef();
					m_noOfLoadedPubs++;
				}
			}
		}
	}


	void LibApp::save() //Changed for MS5
	{
		std::cout << "Saving Data" << std::endl;
		std::ofstream file(m_filename);

		if (!file)
		{
			std::cerr << "Error: Could not open file" << m_filename << std::endl;
			return;
		}

		for (int i = 0; i < m_noOfLoadedPubs; i++)
		{
			if (records[i]->getRef() !=0)
			{
				file << *records[i];
			}
		}
		file.close();
	}


	int LibApp::search(int mode) { //MS5 addition
		PublicationSelector selector("Select one of the following found matches:");
		char title[256];
		char type{};
		int pubType = m_pubMenu.run();

		if (pubType == 0) {
			std::cout << "Aborted!"<<std::endl << std::endl;
			return 0;
		}
		else if (pubType == 1) {
			type = 'B';
		}
		else {
			type = 'P';
		}

		std::cout << "Publication Title: ";
		std::cin.ignore(); 
		std::cin.getline(title, 256);

		for (int i = 0; i < m_noOfLoadedPubs; ++i) {
			if (records[i]->getRef() != 0 &&
				type == records[i]->type() &&
				strstr(*records[i], title)) {

				bool match = false;
				if (mode == 5 && records[i]->onLoan()) {
					match = true;
				}
				else if (mode == 0 && !records[i]->onLoan()) {
					match = true;
				}
				else if (mode == 1) {
					match = true;
				}

				if (match) {
					selector << records[i];
				}
			}
		}

		if (selector) {
			selector.sort();
			int ref = selector.run();

			if (ref) {
				printPublications(records, ref, m_noOfLoadedPubs);
			}
			else {
				std::cout << "Aborted!"<<std::endl << std::endl;
			}

			return ref;
		}
		else {
			std::cout << "No matches found!" << std::endl << std::endl;
			return 0;
		}
	}

	


	void LibApp::returnPub()  //MS5 addition
	{
		std::cout << "Return publication to the library" << std::endl;
		int libRefNum = search(5);
		int days, daysLate;
		double cost;
		Date current;

		if (libRefNum != 0 && confirm("Return Publication?")) {

			days = current - getPub(libRefNum)->checkoutDate();
			daysLate = days - 15;

			if (daysLate > 0) {
				cost = daysLate * 0.5;
				std::cout << "Please pay $";
				std::cout << std::fixed << std::setprecision(2) << cost;
				std::cout << " penalty for being " << daysLate << " days late!" << std::endl;
			}
			getPub(libRefNum)->set(0);
			m_changed = true;
			std::cout << "Publication returned" <<std::endl<< std::endl;
		}

	}

	void LibApp::printPublications(Publication* pub[], int reference, int size)  //MS5 addition
	{
		for (int i = 0; i < size; i++)
		{
			if (pub[i]->getRef() == reference)
			{
				std::cout << *pub[i] << std::endl;
				i = size;
			}
		}
	}

	Publication* LibApp::getPub(int libRefNum)  //MS5 addition
	{
		for (int i = 0; i < m_noOfLoadedPubs; i++)
		{
			if (records[i]->getRef() == libRefNum)
			{
				return records[i];
			}
		}
		return nullptr;
	}

	LibApp::~LibApp() //Addition
	{
		for (int i = 0; i < m_noOfLoadedPubs; i++)
		{
			delete records[i];
		}
	}


}
