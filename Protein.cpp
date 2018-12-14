#include "Protein.h"
#include"DNA.h"
#include<fstream>
#include<iomanip>
using namespace std;
///recursive function that is used in GetDNAStrandsEncodingMe function
///that search for the DNA sequences that can be converted to a RNA sequence
template <class T>
void Protein<T> ::  add_newProtein (const DNA<T> & bigDNA , int i , int SIZE ,int SIZE2,int& index, string temp,DNA<T>* DNAs)
{
    if (i>=SIZE)
    {
        return;
    }
    temp += bigDNA.seq[i];
    if(temp.size() < SIZE2) return add_newProtein(bigDNA , i+1 , SIZE , SIZE2 , index, temp,DNAs);
    if(temp.size() == SIZE2 )
    {
        DNA<T> d(temp) ;
        RNA<T> r ;
        r=d.ConvertToRNA();
        Protein<T> p;
        CodonsTable c;
        p = r.ConvertToProtein(c);
        bool IS = true;
        for (int i =0 ; i<temp.size() ; i++)
        {
            if(p.seq[i] != this->seq[i]) IS = false;
        }
        if(IS == false) return add_newProtein(bigDNA,i-SIZE2+2,SIZE,SIZE2,index,temp="",DNAs);
        DNA<T>* a = new DNA<T>(temp);
        DNAs[index++] = *a;

        return add_newProtein(bigDNA,i+1,SIZE,SIZE2,index,temp="",DNAs);
    }
}
///default constructor
template <class T>
Protein<T>::Protein()
{
    //ctor
}
///parameterized constructor
template<class T>
Protein<T> :: Protein(T*seq): Sequence<T>(seq)
{

}
///destructor
template <class T>
Protein<T>::~Protein()
{
}
///function that print protein sequence and its details
template <class T>
void  Protein<T>::Print()
{
    cout << this ->seq << endl;
}
///function that return all DNA sequences that can be converted to the protein sequence
template<class T>
DNA<T>* Protein<T> :: GetDNAStrandsEncodingMe(const DNA<T> & bigDNA)
{
    int counter = 1 , newB=0 , newE = 8 , SIZE=0;

    for ( int i = 0 ; bigDNA.seq[i]!=NULL ; i+=counter )
    {
        SIZE++;
    }
    int SIZE2 = 0;
    for(int i = 0; this->seq[i]!= NULL; i++) SIZE2++;
    DNA<T>* DNAs = new DNA<T>[100];
    int index = 0;
    add_newProtein(bigDNA,0,SIZE,SIZE2*3,index,"",DNAs);
    DNAs[index] = DNA<T>();
    return DNAs;


}
///overloading for in operator
template <class T>
istream&  operator>>(istream& in,Protein<T>& S)
{
    in>>S.seq;
    return in;
}
///overloading for out operator
template <class T>
ostream& operator<<(ostream& out,Protein<T>& S)
{
    out<<S.seq;
    return out;
}
 ///overloading operator for checking equality
template<class T>
bool Protein<T> :: operator== ( Protein<T> S )
{
    if(type != S.type) return false;
    for(int i=0;; i++)
    {
        if(this->seq[i]!=S.seq[i])
        {
            return false;
        }
        else if(this->seq[i]==NULL)
        {
            break;
        }
    }
    return true;

}
///overloading operator for checking for non-equality
template<class T>
bool Protein<T> :: operator!= ( Protein<T> S )
{

    return(!(*this==S));

}
///overloading for + operator to add 2 Protein sequences
template<class T>
Protein<T> Protein<T>:: operator+ ( Protein<T>& S )
{
    T kk[10000];
    int c=0;
    for(int i=0; this->seq[i]!=NULL; i++)
    {
        kk[i]=this->seq[i];
        c=i;
    }

    int k=0;
    c++;
    for( ;; c++)
    {
        if(S.seq[k]!=NULL)
        {
            kk[c]=S.seq[k];
            k++;

        }
        else
        {
            kk[c]=S.seq[k];
            break;
        }
    }
    Protein<T> w(kk);
    return w;
}
///function to save protein sequence to file
template <class T>
void Protein<T> :: save_Sequence(string fileName)
{
    ofstream file1;
    file1.open(fileName);
    for(int i=0; this->seq[i]!=NULL; i++)
    {
        file1<<this->seq[i];
    }
    file1<<endl;
    file1<<type;
    file1<<endl;
    file1.close();

}
///function to load protein sequence in characters from a file
template<> void Protein<char> :: load_Sequence(string fileName)
{
    ifstream file1;
    file1.open(fileName);
    string typeEnum;
    int i=0;
    while(!file1.eof())
    {
        if(i==0)
        {
            file1>>(this->seq);
        }
      i++;
    }
    file1.close();

}

///function to load protein sequence in ASCII characters from a file
template<> void Protein<int> :: load_Sequence(string fileName)
{
    ifstream file1;
    file1.open(fileName);
    string typeEnum;
    int i=0;
    int index = 0;
    while(!file1.eof())
    {
        string s;
        file1>>s;
        if(s.size() == 1) throw;
        else if (isdigit(s[0]) && isdigit(s[1]) &&  i == 0) this-> seq[index++] = char( s[0]*10 +  s[1] ) , i = 0;
    }
    file1.close();

}
///specializing types which templates can work on
template class Protein<char>;
template class Protein<int>;


