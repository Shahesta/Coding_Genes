#ifndef SEQUENCE_H
#define SEQUENCE_H
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

template <class T>
class Sequence;


template <class T>

class Sequence
{
protected:
    char * seq;
public:
    // constructors and destructor
    Sequence();
    Sequence(T* str);
    Sequence(string str);
    Sequence(Sequence& rhs);
    virtual ~Sequence();
    //function to calculate size of sequences
    int calSize();
    //getter function to get the private attribute seq
    string getSeq();
    // pure virtual function that should be overridden because every
    // type of sequence has its own details to be printed
    virtual void Print()= 0;

    // friend function that will find the LCS (longest common
    // subsequence) between 2 sequences of any type, according to
    // polymorphism
    template<class C>
    friend char* Align(Sequence<C> * s1, Sequence<C> * s2);
    //operator overloading to out operator
    template <class C>
    friend ostream& operator<< (ostream& out, Sequence<C>* s);
    template<class O>
    friend void getMinimumPenalty(Sequence<O>* x, Sequence<O>* y, int pxy, int pgap);
    //function to save sequence to file
    virtual void save_Sequence(string fileName)=0;
    //function to load sequence from file
    virtual void load_Sequence(string fileName)=0;

};

template <class C>
ostream& operator<< (ostream& out, Sequence<C>* s)
{
    s -> Print();
    return out;
}
///alignment function to compare 2 sequences and get the longest common sequence
template<class C>
char* Align(Sequence<C> * s1, Sequence<C> * s2)
{
    char LCS_chars[1000]= {0};
    int len1 = s1->calSize();///get size of first sequence
    int len2 = s2->calSize(); ///get size of second sequence
    int length[len1+1][len2+1];
    int c = 0; ///counter to insert the chars in LCS
    int j=0, i=0;

    for ( i=0 ; s1->seq[i]!=NULL  ; i++)
    {
        for ( j=0 ; s2->seq[j]!=NULL  ; j++)
        {

            if(i==0||j==0)
                length[i][j]=0;
            else if (s1->seq[i-1]==s2->seq[j-1] )
            {
                length[i][j]=length[i-1][j-1]+1;

            }
            else
                length[i][j]=max(length[i][j-1],length[i-1][j]);
        }

    }

    int lcs = length[i-1][j-1];///length of common sequence
    LCS_chars [ lcs + 1]; /// make C_string to store common sequence with length lcs
    LCS_chars[ lcs ]= NULL ; /// terminating last char

    while (i > 0 && j > 0)
    {
        if ( s1->seq[i-1] == s2->seq[j-1]  )
        {
            LCS_chars[ lcs ] = s1->seq[i-1];
            lcs--;
            i--;
            j--;

        }
        else if ( length[i][j-1] > length[i-1][j] )
            j--;

        else
            i--;
    }

    return LCS_chars;
}

template<class O>
void getMinimumPenalty(Sequence<O>* x, Sequence<O>* y, int pxy, int pgap)
{
    int i, j; // intialising variables

    int m = strlen(x.getSeq()); // length of gene1
    int n = strlen(y.getSeq()); // length of gene2

    // table for storing optimal substructure answers
    int dp[300][300] = {0};

    // intialising the table
    for (i = 0; i <= (n+m); i++)
    {
        dp[i][0] = i * pgap;
        dp[0][i] = i * pgap;
    }

    // calcuting the minimum penalty
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (x->seq[i - 1] == y->seq[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min({dp[i - 1][j - 1] + pxy ,
                                dp[i - 1][j] + pgap    ,
                                dp[i][j - 1] + pgap    });
            }
        }
    }

    // Reconstructing the solution
    int l = n + m; // maximum possible length

    i = m; j = n;

    int xpos = l;
    int ypos = l;

    // Final answers for the respective strings
    int xans[300], yans[300];

    while ( !(i == 0 || j == 0))
    {
        if (x->seq[i - 1] == y->seq[j - 1])
        {
            xans[xpos--] = (int)x->seq[i - 1];
            yans[ypos--] = (int)y->seq[j - 1];
            i--; j--;
        }
        else if (dp[i - 1][j - 1] + pxy == dp[i][j])
        {
            xans[xpos--] = (int)x->seq[i - 1];
            yans[ypos--] = (int)y->seq[j - 1];
            i--; j--;
        }
        else if (dp[i - 1][j] + pgap == dp[i][j])
        {
            xans[xpos--] = (int)x->seq[i - 1];
            yans[ypos--] = (int)'_';
            i--;
        }
        else if (dp[i][j - 1] + pgap == dp[i][j])
        {
            xans[xpos--] = (int)'_';
            yans[ypos--] = (int)y->seq[j - 1];
            j--;
        }
    }
    while (xpos > 0)
    {
        if (i > 0) xans[xpos--] = (int)x->seq[--i];
        else xans[xpos--] = (int)'_';
    }
    while (ypos > 0)
    {
        if (j > 0) yans[ypos--] = (int)y->seq[--j];
        else yans[ypos--] = (int)'_';
    }

    // Since we have assumed the answer to be n+m long,
    // we need to remove the extra gaps in the starting
    // id represents the index from which the arrays
    // xans, yans are useful
    int id = 1;
    for (i = l; i >= 1; i--)
    {
        if ((char)yans[i] == '_' && (char)xans[i] == '_')
        {
            id = i + 1;
            break;
        }
    }

    // Printing the final answer
    cout << "Minimum Penalty in aligning the genes = ";
    cout << dp[m][n] << "\n";
    cout << "The aligned genes are :\n";
    for (i = id; i <= l; i++)
    {
        cout<<(char)xans[i];
    }
    cout << "\n";
    for (i = id; i <= l; i++)
    {
        cout << (char)yans[i];
    }
    return;
}

#endif // SEQUENCE_H
