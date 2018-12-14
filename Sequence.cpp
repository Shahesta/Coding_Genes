#include "Sequence.h"
#include<fstream>
#include<iomanip>


///default constructor
template <class T>
Sequence<T>::Sequence()
{
    seq = new char [100000];

}
///parameterized constructor
template <class T>
Sequence<T> :: Sequence ( T* str )
{
    seq = new char [100000];
    int i = 0;
    for ( ; str[i] != NULL ; i++ )
    {
        seq[i] = str[i];
    }
    seq[i] = 0;
}
///destructor
template <class T>
Sequence<T>::~Sequence()
{
    //dtor
}
///function to calculate the size of the sequence
template <class T>
int Sequence<T>:: calSize()
{
    int i = 0;
    for(; seq[i] != NULL; i++) {}
    return i;
}

///parameterized constructor with string parameter
template <class T>
Sequence<T> :: Sequence(string str)
{
    seq = new char [100000];
    int i = 0;
    for ( ; str[i] != NULL ; i++ )
    {
        seq[i] = str[i];
    }
    seq[i] = 0;
}
///copy constructor
template <class T>
Sequence<T> :: Sequence(Sequence& rhs)
{

    seq = new char [100000];
    int i = 0;
    for(; rhs.seq[i] != NULL; i++)
        seq[i] = rhs.seq[i];
    seq[i] = 0;
}
///function to save the sequence in a file
template <class T>
void Sequence<T> :: save_Sequence( string filename)
{
    ofstream file1;
    file1.open(filename);
    for(int i=0; seq[i]!=NULL; i++)
    {
        file1<<seq[i];
    }
    file1.close();


}
///overloading for operator == to compare between 2 sequences and check whether they are equal

///getter function to access private attribute "sequence" from outside the class
template < class T >
string Sequence<T> :: getSeq()
{
    string str;
    for(int i = 0;this->seq[i] != NULL;i++)
        str = str + this->seq[i];
    return str;
}
///overloading for operator += to add 2 sequences

///specializing types which templates can work on
template class Sequence<char>;
template class Sequence<int>;
