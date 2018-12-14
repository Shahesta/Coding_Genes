#ifndef PROTEIN_H
#define PROTEIN_H
#include"sequence.h"
#include<iostream>
#include"CodonsTable.h"
using namespace std;
template<class T>
class DNA;

//enum has PROTEIN types
enum Protein_Type {Hormon, Enzyme, TF, Cellular_Function};
template <class T>
class Protein : public Sequence<T>
{
private:
    Protein_Type type;
public:
    // constructors and destructor
    Protein();
    Protein(T * seq);
    ~Protein();
    //function to print RNA sequence ans its details
    void Print();
    // return an array of DNA sequences that can possibly
    // generate that protein sequence
    DNA<T>* GetDNAStrandsEncodingMe(const DNA<T> & bigDNA);
    //recursive function that is used in GetDNAStrandsEncodingMe to search for the DNA sequences that can be converted to that protein
    void  add_newProtein (const DNA<T> & bigDNA , int i , int SIZE ,int SIZE2,int& index, string temp,DNA<T>* DNAs);
    //overloading for in operator
    friend istream& operator>> (istream& in , Protein<T>& S);
    //overloading for out operator
    friend ostream& operator<< (ostream& out , Protein<T>& S);
     //overloading operator for checking equality
    bool operator== ( Protein<T> S );
    //overloading operator for checking for non-equality
    bool operator!= ( Protein<T> S );
    //overloading for + operator to add 2 Protein sequences
    Protein operator+ ( Protein<T>& S );
    //function to save PROTEIN sequence to file
    void save_Sequence(string fileName);
    //function to load PROTEIN sequence from file
    void load_Sequence(string fileName);


};


#endif // PROTEIN_H
