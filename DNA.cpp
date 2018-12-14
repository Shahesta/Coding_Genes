#include "DNA.h"
#include "RNA.cpp"
#include<fstream>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;
///default constructor
template < class T>
DNA<T>::DNA()
{
    type = promoter;
    startIndex = 0;
    endIndex = 0;
    complementary_strand = NULL;
    //ctor
}
///parameterized constructor
template <class T>
DNA<T> ::  DNA(T * seq, DNA_Type atype) : Sequence<T>(seq)
{
    type = atype;
    startIndex = 0;
    endIndex = strlen(this->seq)-1;
    complementary_strand = NULL;

}
///getter function to get the private attribute "ENDINDEX"
template < class T>
int DNA<T> :: getEndIndex()
{
    return endIndex;
}
///parameterized constructor
template <class T>
DNA<T> :: DNA(string str) : Sequence<T>(str)
{
    complementary_strand = NULL;
    startIndex = 0;
    endIndex = str.size();
}
///copy constructor
template <class T>
DNA<T> :: DNA(const DNA& rhs) :  Sequence<T>(rhs.seq)
{
    type=rhs.type;
    complementary_strand= new DNA;
    *complementary_strand=*(rhs.complementary_strand);
    complementary_strand=NULL;

    startIndex=rhs.startIndex;
    endIndex=rhs.endIndex;
}
///print function to print DNA sequence and its details
template <class T>
void DNA<T> :: Print()
{

    cout << "type is : ";
    if ( promoter==type )
    {
        cout << "promoter" << endl;
    }
    if ( motif==type )
    {
        cout << "motif" << endl;
    }
    if ( tail==type )
    {
        cout << "tail" << endl;
    }
    if ( noncoding==type )
    {
        cout << "noncoding" << endl;
    }
    BuildComplementaryStrand();
    cout << "The main strand is:  "<< this -> seq << endl;

    cout<<"The complementry strand is : "<<complementary_strand->seq << endl;
}
///fuction to build the complementary strand for the DNA sequence "the other strand "
template <class T>
void DNA<T> :: BuildComplementaryStrand()
{
    string seq1;
    int c=startIndex;
    for(int i=0; i<(endIndex-startIndex+1); ++i)
    {
        switch(this->seq[c])
        {
        case 'T':
            seq1+='A';
            break;
        case 'A':
            seq1+='T';
            break;
        case 'C':
            seq1+='G';
            break;
        case 'G':
            seq1+='C';
            break;
        }
        c++;
    }
    reverse(seq1.begin(),seq1.end());
    int s=0;
    char seq2[1000];
    for(int i=0; i<seq1.length(); i++)
    {
        seq2[i]=seq1[i];
        s=i;

    }
    s++;
    seq2[s]=NULL;
    complementary_strand= new DNA<T>(seq1);
}
///function to convert the DNA sequence to RNA sequence
template <class T>

RNA<T> DNA<T> :: ConvertToRNA()
{
    int c=0;
    T str[10000];

    for(int i=0,j=startIndex; this->seq[i]!=NULL && j <= endIndex; i++,j++)
    {
        if(this->seq[j]=='T')
        {
            str[i]='U';
        }
        else
        {
            str[i]=this->seq[j];
        }
        c=j;
    }
    str[c+1]=NULL;
    RNA<T> b(str,mRNA);

    return b;


}
///overloading for in operator
template <class T>
istream&  operator>>(istream& in,DNA<T>& S)
{
    in>>S.seq;
    return in;
}
///overloading for out operator
template < class T>
ostream& operator<<(ostream& out, DNA<T>& S)
{
    out << S.seq << endl;
    return out;
}
///overloading for operator == to compare between 2 sequences and check whether they are equal
template<class T>
bool DNA<T> :: operator== ( DNA<T> S )
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
///overloading for the non-equality operator
template <class T>
bool DNA<T> :: operator!= ( DNA S )
{

    return(!(*this==S));

}
///overloading for + operator to add 2 DNA sequences
template <class T>
DNA<T> DNA<T> :: operator+ (const DNA<T>& S )
{
    char kk[10000];
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
    DNA<T> w(kk);

    return w;
}
///destructor
template <class T>
DNA<T>::~DNA()
{
    //dtor
}
///function to save DNA sequence to a file
template <class T>
void DNA<T> :: save_Sequence(string fileName)
{
    ofstream file1;
    file1.open(fileName);

    file1<<this->seq;
    file1<<endl;
    file1<<this->type;
    file1<<endl;
    BuildComplementaryStrand();
    file1<<this->complementary_strand->seq;
    file1.close();

}
///function to load DNA sequence as characters and its details from a file
template<> void DNA<char> :: load_Sequence(string fileName)
{
    ifstream file1;
    file1.open(fileName);
    ///need exception handling
    string typeEnum;
    int i=0;
    while(!file1.eof())
    {
        if(i==0)
        {

            file1>>(this->seq);

        }

        else if(i==1)
        {
            file1>>typeEnum;
            if(typeEnum=="promoter")
            {
                type=promoter;
            }
            else if(typeEnum=="motif")
            {
                type=motif;
            }
            else if(typeEnum=="tail")
            {
                type=tail;
            }
            else if(typeEnum=="noncoding")
            {
                type=noncoding;
            }
            else if(typeEnum=="noncoding")
            {
                type=noncoding;
            }

        }

        i++;
    }
    file1.close();

}

///function to load DNA sequence as ASCII characters and its details from a file
template<> void DNA<int> :: load_Sequence(string fileName)
{
    ifstream file1;
    file1.open(fileName);
   ///need exception handling
    string typeEnum;
    int i=0;
    int index = 0;
    while(!file1.eof())
    {


        string s;
        file1>>s;
        if(s.size() == 1) throw;
        else if (isdigit(s[0]) && isdigit(s[1]) &&  i == 0) this-> seq[index++] = char( s[0]*10 +  s[1] ) , i = 0;
        else if(i == 0)
        {
            i = 1;


            file1>>typeEnum;
            if(typeEnum=="promoter")
            {
                type=promoter;
            }
            else if(typeEnum=="motif")
            {
                type=motif;
            }
            else if(typeEnum=="tail")
            {
                type=tail;
            }
            else if(typeEnum=="noncoding")
            {
                type=noncoding;
            }
            else if(typeEnum=="noncoding")
            {
                type=noncoding;
                i++;
            }
        }
        else if(i == 3)
        {
            int index1 , index2;
            file1 >> index1 >> index2;
            if(index1 == -1 && index2 == -1) index1 = 0 , index2 = strlen(this -> seq)-1;
        }


    file1.close();
    }

}

///specializing types which templates can work on
template class DNA<char>;
template class DNA<int>;

