/*
Citation and Sources...
Final Project Milestone 2
Module: LibApp
Filename: LibApp.h
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

#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include <cstring>

#include "Menu.h"
#include "Lib.h"
#include "Publication.h"


namespace sdds {
   class LibApp {
	   bool m_changed;
	   Menu m_mainMenu;
	   Menu m_exitMenu;
	   Menu m_pubMenu;

	   //MS5 additions
	   char m_filename[256];
	   Publication* records[SDDS_LIBRARY_CAPACITY]{};
	   int m_noOfLoadedPubs;
	   int m_lastLibraryRefNum;

	   
	   // Simple methods
	   bool confirm(const char* message);
	   void load();  // prints: "Loading Data"<NEWLINE>
	   void save();  // prints: "Saving Data"<NEWLINE>
	   int search(int mode=1);  // New: Added an argument(option) for the search method

	   void returnPub();  /*  Calls the search() method.
							  prints "Returning publication"<NEWLINE>
							  prints "Publication returned"<NEWLINE>
							  sets m_changed to true;
						  */

	   
	   void newPublication();
	   void removePublication();
	   void checkOutPub();

	   void printPublications(Publication* pub[], int reference, int size);

	   Publication* getPub(int libRefNum);

	   
   public:
	   LibApp(const char* filename);
	   void run();
	   ~LibApp();
	  

   };
}
#endif // !SENECA_LIBAPP_H



