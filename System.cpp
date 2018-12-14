#include "System.h"
#include <iostream>

using namespace std;
///function to show choices user can choose to work on a coding gene
void System :: showMenu()
{
    cout << "1- Load Sequence1" << endl
         << "2- Save Sequence1 to file" << endl
         << "3- Enter another sequence of the same type then get the LCS" << endl
         << "4- Enter another sequence of the same type then get the global alignment" << endl
         << "5- Print details " << endl
         << "6- Enter a sequence of the same type then compare it to Sequence1" << endl
         << "7- Enter a sequence then print the result of adding it to sequence1" << endl
         << "8- Convert Sequence1 to DNA and print" << endl
         << "9- Convert Sequence1 to RNA and print" << endl
         << "10- Convert Sequence1 to Protein and print" << endl
         << "11- Exit" << endl;
}
///intro function to the program
void System :: showIntro()
{
    cout << "Welcome to Coding Genes System" << endl
         << "Enter 0 if you will enter ASCII , 1 if you enter as chars" << endl;
}
