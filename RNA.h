#ifndef RNA_H
#define RNA_H
#include"sequence.h"
#include"Protein.h"
#include"CodonsTable.h"
#include<iostream>
using namespace std;
//enum has RNA types
enum RNA_Type {mRNA, pre_mRNA, mRNA_exon, mRNA_intron};

template <class T>
class DNA ;

template <class T>
class RNA : public Sequence<T>
{

private:
    RNA_Type type;
public:
    // constructors and destructor
    RNA();
    RNA(T * seq, RNA_Type atype);
    RNA(const RNA& rhs);
    ~RNA();
    // function to be overridden to print all the RNA information
    void Print();
    // function to convert the RNA sequence into protein sequence
    // using the codonsTable object
    Protein<T> ConvertToProtein(const CodonsTable & table);
    // function to convert the RNA sequence back to DNA
    DNA<T> ConvertToDNA();
    //recursive function that is used in GetDNAStrandsEncodingMe to search for the DNA sequences
    //that can be converted to that protein
    //using converting to RNA
    friend void Protein<T> ::  add_newProtein (const DNA<T> & bigDNA , int i , int SIZE ,int SIZE2,int& index, string temp,DNA<T>* DNAs);
    //overloading for in operator
    friend istream& operator>> (istream& in , RNA & S);
    //overloading for out operator
    friend ostream& operator<< (ostream& out ,const RNA& S);
     //overloading operator for checking equality
    bool operator== ( RNA S );
    //overloading operator for checking for non-equality
    bool operator!= ( RNA S );
    //overloading for + operator to add 2 RNA sequences
    RNA operator+ ( RNA& S );
    //function to save RNA sequence to file
    void save_Sequence(string fileName);
    //function to load RNA sequence from file
    void load_Sequence(string fileName);

};

#endif // RNA_H
