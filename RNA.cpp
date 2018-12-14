#include "RNA.h"
#include "DNA.h"
#include<fstream>
#include<iomanip>

///default constructor
template <class T>
RNA<T>::RNA()
{
    //ctor
}
///parameterized constructor
template<class T>
RNA<T> :: RNA(T * seq, RNA_Type atype) : Sequence<T> (seq)
{
    type = atype ;

}
///copy constructor
template <class T>
RNA <T>:: RNA(const RNA& rhs): Sequence<T>(rhs.seq)
{
    type =  rhs.type;


}
///destructor
template <class T>
RNA<T>::~RNA()
{
}
///function to print RNA sequence and its details
template <class T>
void RNA<T> :: Print()
{

    cout << "type is : ";
    if ( mRNA==type )
    {
        cout << "mRNA" << endl;
    }
    if ( pre_mRNA==type )
    {
        cout << "pre_mRNA" << endl;
    }
    if ( mRNA_exon==type )
    {
        cout << "mRNA_exon" << endl;
    }
    if ( mRNA_intron==type )
    {
        cout << "mRNA_intron" << endl;
    }
    cout << this -> seq << endl;


}
///function to convert RNA sequence to DNA sequence
template<class T>
DNA<T> RNA<T> :: ConvertToDNA()
{
    int c=0;
    T str[10000];
    for(int i=0; this-> seq[i]!=NULL; i++)
    {
        if(this ->seq[i]=='U')
        {
            str[i]='T';
        }
        else
        {
            str[i]=this ->seq[i];
        }
        c=i;
    }
    str[c+1]=NULL;
    DNA<T> b(str,promoter);
    return b;
}
///function to convert RNA sequence to protein sequence
template < class T>
Protein<T> RNA<T> :: ConvertToProtein(const CodonsTable & table)
{

    char value[4];
    T arr[305];
    char amino;
    int j=0;
    //cout << 111 << endl;
    for(int i=0; this -> seq[i]!=NULL; i+=3)
    {
        value[0]=this -> seq[i];
        value[1]=this -> seq[i+1];
        value[2]=this -> seq[i+2];
        value[3] = NULL;
        //cout << 1 << endl;
        amino=table.getAminoAcid(value);
        arr[j++]=amino;

    }
    arr[j]=NULL;

    Protein<T> b(arr);

    return b;
}
///overloading for in operator
template <class T>
istream&  operator>>(istream& in,RNA<T>& S)
{
    in>>S.seq;
    return in;
}
///overloading for out operator
template <class T>
ostream& operator<<(ostream& out,const RNA<T>& S)
{
    out<<S.seq;
    return out;
}
///overloading operator for checking equality
template <class T>
bool RNA<T> :: operator== ( RNA<T> S )
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
template <class T>
bool RNA<T> :: operator!= ( RNA<T> S )
{

    return(!(*this==S));

}
//overloading for + operator to add 2 RNA sequences
template <class T>
RNA<T> RNA<T> :: operator+ ( RNA<T>& S )
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
    RNA<T> w(kk,mRNA);
    return w;
}
///function to save RNA sequence to file
template <class T>
void RNA<T> :: save_Sequence(string fileName)
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
///function to load RNA sequence in characters from a file
template<> void RNA<char> :: load_Sequence(string fileName)
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
            i++;

        }

        else if(i==1)
        {
            file1>>typeEnum;
            if(typeEnum=="mRNA")
            {
                type=mRNA;
            }

            else if(typeEnum=="pre_mRNA")
            {
                type=pre_mRNA;
            }
            else if(typeEnum=="mRNA_exon")
            {
                type=mRNA_exon;
            }
            else if(typeEnum=="mRNA_intron")
            {
                type=mRNA_intron;
            }

        }

        i++;
    }
    file1.close();

}
///function to load RNA sequence in ASCII characters from a file
template<> void RNA<int> :: load_Sequence(string fileName)
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
        else if(i == 0)
        {
            i = 1;
            file1>>typeEnum;
            if(typeEnum=="mRNA")
            {
                type=mRNA;
            }

            else if(typeEnum=="pre_mRNA")
            {
                type=pre_mRNA;
            }
            else if(typeEnum=="mRNA_exon")
            {
                type=mRNA_exon;
            }
            else if(typeEnum=="mRNA_intron")
            {
                type=mRNA_intron;
            }

        }
    }

    file1.close();

}
template class RNA<int>;
template class RNA<char>;

