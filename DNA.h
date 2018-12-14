#ifndef DNA_H
#define DNA_H
#include"sequence.h"
#include"RNA.h"
#include<iostream>
#include"Protein.h"
using namespace std;
//enum has the types of DNA
enum DNA_Type {promoter, motif, tail, noncoding};

template <class T>
class DNA : public Sequence<T>
{
private:
    DNA_Type type ;
    DNA * complementary_strand;
    int startIndex;
    int endIndex;

public:
    //constructors and destructor
    DNA();
    DNA (T * seq, DNA_Type atype);
    DNA (const DNA& rhs);
    DNA(string str);
     ~DNA();
    //getter function to get the private attribute endIndex
    int getEndIndex();
    //function to print the DNA sequence and all its details
    void Print();
    //function to convert DNA sequence to RNA sequence
    RNA<T> ConvertToRNA();
    //function to build the complementary strand " the other strand " of the DNA sequence
    void BuildComplementaryStrand();
    //function to get the DNA sequences that can be converted to a definite RNA sequence
    friend DNA<T>* Protein<T> :: GetDNAStrandsEncodingMe(const DNA<T> & bigDNA);
    //recursion function that is used in GetDNAStrandsEncodingMe
    //to search for the DNA sequences that can convert to the protein sequence
    friend void Protein<T> ::  add_newProtein (const DNA<T> & bigDNA , int i , int SIZE ,int SIZE2,int& index, string temp,DNA* DNAs);
    //overloading for in operator
    friend istream& operator>> (istream& in , DNA<T>& S);
    //overloading for out operator
    friend ostream& operator<< (ostream& out ,  DNA<T>& S);
    //overloading operator for checking equality
    bool operator== ( DNA<T> S );
    //overloading operator for checking for non-equality
    bool operator!= ( DNA<T> S );
    //overloading for + operator to add 2 DNA sequences
    DNA operator+ ( const DNA<T>& S );
     //function to save DNA sequence to file
    void save_Sequence(string fileName);
    //function to load DNA sequence from file
    void load_Sequence(string fileName);

protected:

};

#endif // DNA_H
