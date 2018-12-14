#include "CodonsTable.h"
#include"Protein.h"
#include<fstream>
#include<iomanip>
#include <string>


///default constructor
CodonsTable::CodonsTable()
{
    ifstream file1("RNA_codon_table.txt");
    int j=0;
    char s[6];
    while(!file1.eof())
    {
        char s[6];
        file1 >> s;
        int siz=0;
        for(int i=0; s[i]!=NULL; i++)
        {
            siz++;
        }

        for(int i=0; i<3; i++)
        {
            codons[j].value[i]=s[i];
        }
        if(siz==3)
        {
            codons[j].value[3]=NULL;
            codons[j].AminoAcid=NULL;
        }
        codons[j].value[3]=NULL;
        codons[j].AminoAcid=s[3];
        j++;
    }
    file1.close();
}
///copy constructor
CodonsTable::CodonsTable (const CodonsTable& c)
{

    for(int i=0; i<64; i++)
    {
        for(int j=0; j<4; j++)
        {
            codons[i].value[j]=c.codons[i].value[j];
        }
        codons[i].AminoAcid=c.codons[i].AminoAcid;
    }

}
///destructor
CodonsTable::~CodonsTable()
{

}
///function to load codons and its amino acids in an array of codon
void CodonsTable :: LoadCodonsFromFile(string codonsFileName)
{
    ifstream file1(codonsFileName);
    int j=0;

    while(!file1.eof())
    {
        char s[6];
        cin.ignore();
        file1.getline(s,6);
        for(int i=0; i<3; i++)
        {
            codons[j].value[i]=s[i];
        }
        codons[j].value[3]=NULL;
        codons[j].AminoAcid=s[3];
        j++;

    }
    file1.close();



}
///function to get the amino acid of a given codon
char CodonsTable :: getAminoAcid (char * value) const
{
    bool isFound=false;
    char aminoAcid;
    for(int i=0; isFound!=true; i++)
    {
        bool isF=true;
        for(int j=0; j<3; j++)
        {
            if(codons[i].value[j]!=value[j])
            {
                isF=false;
                break;
            }
        }
        if(isF==true)
        {

            aminoAcid=codons[i].AminoAcid;
            isFound=true;
        }


    }
    return aminoAcid;

}

///setter function to reset a codon and its amino acid in the array
void CodonsTable :: setCodon(char * value, char AminoAcid, int index)
{

    codons[index].AminoAcid=AminoAcid;
    for(int i=0; i<3; i++)
    {
        codons[index].value[i]=value[i];
    }

}
