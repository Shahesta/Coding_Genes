#ifndef CODONSTABLE_H
#define CODONSTABLE_H
using namespace std;
#include<string>
template <class T>
class Protein;

// struct representing a codon of 3 DNA/RNA characters and ‘\0’
struct Codon
{
    char value[4];    	    // 4th location for null character
    char AminoAcid;  	    // corresponding AminoAcid according to Table
};

// need to create one object of that class to load the AminoAcids table
// into memory
class CodonsTable
{
private:
    Codon codons[64];
public:
    template<class T>
    friend class RNA; //defining RNA class as a friend class to access private and protected attributes
    template<class T>
    friend class Protein;//defining protein class as a friend class to access private and protected attributes
    // constructors and destructor
    CodonsTable();
    CodonsTable(const CodonsTable& c) ;
    ~CodonsTable();
    // function to load all codons from the given text file
    void LoadCodonsFromFile(string codonsFileName);
    char getAminoAcid (char * value) const;
    void setCodon(char * value, char AminoAcid, int index);

};
#endif
