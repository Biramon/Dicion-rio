/* Classe lista sequencial. */
#include <iostream>
#include <sstream>
#include <cmath>
#include <functional>
#include "arraylist.h"
#define tam 50

template <typename Key>
class myComparator {
	public:
	int operator() (Key _lhs, Key _rhs)
	{
		if (_lhs > _rhs) {
			return 1;
		} else if (_lhs == _rhs) {
			return 0;
		} else {
			return -1;
		}
	}
};


int main ( ) {


    ArrayList< int, std::string, myComparator <int>  >  myList( tam ); 
    SortedArrayList <int, std::string, myComparator<int> > mySortedList( tam );

    std::cout << "\n>>> Inital myList: " << myList << std::endl;


    myList.insert( 15, "dado 1" );
    myList.insert( 2, "dado 2" );
    myList.insert( 8, "dado 3" );
    myList.insert( 10, "dado 4" );
    std::cout << "\n>>> myList after some insertions: \n" << myList << std::endl;

    
    std::cout << "\n>>> Removing from myList, the memory block with Key = 15: " << std::endl;
    std::string recData ("NO DATA");
    myList.remove(15, recData);
    std::cout << "Data removed was: " <<  "'" << recData << "'"<< std::endl;
    std::cout << "\n>>> Now, myList is: \n" << myList << std::endl;


    std::cout << "\n>>> Removing from myList, the memory block with Key = 5: " << std::endl;
    recData = "NO DATA TO REMOVE";
    myList.remove(5, recData);
    std::cout << "Data removed was: " <<  "'" << recData << "'"<< std::endl;
    std::cout << "\n>>> Now, myList is: \n" << myList << std::endl;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    std::cout << "\n\n\n>>> Initial mySortedList (Sorted by Key) : " << mySortedList << std::endl;


    mySortedList.insert(15, "dado 1");
    mySortedList.insert(2, "dado 2");
    mySortedList.insert(8, "dado 3");    
    mySortedList.insert( 10, "dado 4" );
    std::cout << "\n>>> mySortedList after some insertions: \n" << mySortedList << std::endl;
    

    std::cout << "\n>>> Removing from mySortedList, the memory block with Key = 2: " << std::endl;
    std::string recData2 ("NO DATA");
    mySortedList.remove(2, recData2);
    std::cout << "Data removed was: " << "'" << recData2 << "'" << std::endl;
    std::cout << "\n>>> Now, mySortedList is: \n" << mySortedList << std::endl;


    std::cout << "\n>>> Removing from mySortedList, the memory block with Key = 20: " << std::endl;
    recData2 = "NO DATA TO REMOVE";
    mySortedList.remove(20, recData2);
    std::cout << "Data removed was: " << "'" << recData2 << "'" << std::endl;
    std::cout << "\n>>> Now, mySortedList is: \n" << mySortedList << std::endl;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    

    std::cout << "\n>>> Normal ending...\n\n";
    return EXIT_SUCCESS;
}

