#include <iostream>
#include"Sequence.h"
#include"DNA.h"
#include"RNA.h"
#include "exceptions.h"
#include "System.h"
#include <set>
using namespace std;

template < class T>
void check(T*s, int choice1)
{
    if(choice1 == 1)
    {
    set<char> ss = {'A','T','C','G'};
    for(int i = 0;s[i] != NULL;i++)
        if(ss.count(s[i]) == 0)
            throw strangeCharDNA();
    }
    else if(choice1 == 2)
    {
    set<char> ss = {'A','U','C','G'};
    for(int i = 0;s[i] != NULL;i++)
        if(ss.count(s[i]) == 0)
            throw strangeCharRNA();
    }
    else
    {
        set<char> ss = {'k','N','T','R','S','I','M','Q','H','P','R','L','E','D','A','G','V','Y','C','W','L','F'};
    for(int i = 0;s[i] != NULL;i++)
        if(ss.count(s[i]) == 0)
            throw strangeCharProtein();
    }

}

int main()
{
    try
    {
        bool isChar = false;
    int choice1;
    Sequence<char>* s1 = new DNA<char>("ATA",promoter);
    Sequence<char>*s2;
    Sequence<int>* s11;
    Sequence<int>*s22;
   /// cout << s1 << endl;
    System().showIntro();
    cin >> isChar;
    while(true)
    {
        if (isChar)
        {
            System().showMenu();
            int choice;
            cin >> choice;
            if(choice > 11 || choice < 1 ) throw notAvailableChoice();
            if(choice == 1)
            {

                cout << "Enter the type of the sequence \n 1- DNA \n 2- RNA \n 3- Protein" << endl;
                cin >> choice1;
                if(choice1 == 1)  s1 = new DNA<char>;
                else if(choice1 == 2) s1 = new RNA<char>;
                else if(choice1 == 3) s1 = new Protein<char>;
                else  throw notAvailableChoice();
                cout << "Enter 2 if you want to load from file, 1 throw console" << endl;
                cin >> choice;
                if(choice == 1)
                {
                    char sss[1000] = {0};
                    cout << "Enter the Sequence";
                    cin >> sss;
                    check(sss , choice1);
                    if(choice1 == 1)  {
                         s1 = new DNA<char>(sss);

                    }
                    else if(choice1 == 2)
                    {
                          s1 = new RNA<char>(sss,mRNA);
                    }

                    else if(choice1 == 3)
                    {
                          s1 = new Protein<char>(sss);
                    }

                }
                else if(choice == 2)
                {
                    string ss;
                    cout << "Enter FILE NAME : " << endl;
                    cin >> ss;
                    s1-> load_Sequence(ss);
                }
                else throw notAvailableChoice();
            }
            else if(choice == 2)
            {
                cout << "Enter the file name you want to save to " << endl;
                string ss;
                cin >> ss;
                s1-> save_Sequence(ss);
            }
            else if(choice == 3)
            {
                char str[1000] = {0};
                cout << "Enter the sequence : " << endl;
                cin >> str;
                check(str,choice1);
                if(choice1 == 1) s2 = new DNA<char>(str,promoter);
                else if(choice1 == 2) s2 = new RNA<char>(str,mRNA);
                else s2 = new Protein<char>(str);
                cout << "the result of align is : " << Align(s1,s2) << endl;

            }
            else if(choice == 5) s1->Print();
            else if(choice == 6 )
            {
                char str[1000] = {0};
                cout << "Enter the sequence : " << endl;
                cin >> str;
                check(str,choice1);
                if(choice1 == 1) s2 = new DNA<char>(str,promoter);
                else if(choice1 == 2) s2 = new RNA<char>(str,mRNA);
                else s2 = new Protein<char>(str);
                if(s1->getSeq() == s2->getSeq()) cout << "The sequences are identical " << endl;
                else cout << "The sequences are different " << endl;

            }
            else if(choice == 7)
            {
                char str[1000] = {0};
                cout << "Enter the sequence : " << endl;
                cin >> str;
                check(str,choice1);
                if(choice1 == 1) s2 = new DNA<char>(str,promoter);
                else if(choice1 == 2) s2 = new RNA<char>(str,mRNA);
                else s2 = new Protein<char>(str);
                cout << "The result of adding sequences : " << s1->getSeq()+s2->getSeq() << endl;
            }
            else if(choice == 8)
            {
                if(choice1 == 1) throw WrongConversion();
                else if(choice1 == 2) cout << ( dynamic_cast<RNA<char>*>(s1) ) -> ConvertToDNA().getSeq() << endl;

                else
                {
                    cout << "Enter the big DNA Sequence" << endl;
                    char str[1000] = {0};
                    cin >> str;
                    check(str,1);
                    DNA<char> big(str,promoter);
                    DNA<char>* DNAs = ( static_cast<Protein<char>*>(s1) ) -> GetDNAStrandsEncodingMe(big);
                    cout << "The possible DNAs are : " << endl;
                    for(int i = 0; DNAs[i].getEndIndex() != 0; i++)
                        cout << DNAs[i].getSeq() << endl;

                }
            }
            else if(choice == 9)
            {
                if(choice1 == 1) cout << static_cast<DNA<char>*>(s1) -> ConvertToRNA().getSeq() << endl;
                else  throw WrongConversion();

            }
            else if(choice == 10 )
            {
                if(choice1 == 1)
                {
                    RNA<char> a = static_cast<DNA<char>*>(s1) -> ConvertToRNA();
                    cout << " The converted Sequence :  "  << a.ConvertToProtein(CodonsTable()).getSeq() << endl;
                }
                else if(choice1 == 2)
                {
                    cout << "The converted Sequence : " << static_cast<RNA<char>*>(s1) -> ConvertToProtein(CodonsTable()).getSeq() << endl;
                }
                else throw WrongConversion();
            }
            else if(choice == 11) break;


        }

        else
        { System().showMenu();
            int choice;
            cin >> choice;
            if(choice > 11 || choice < 1 ) throw notAvailableChoice();
          if(choice == 1)
            {
                int sss[1000] = {0};
                cout << "Enter the type of the sequence \n 1- DNA \n 2- RNA \n 3- Protein" << endl;
                cin >> choice1;

                cout << "Enter 2 if you want to load from file, 1 throw console" << endl;
                cin >> choice;
                if(choice == 1){   cout << "Enter the length of the sequence" << endl;
                int length; cin >> length;
                cout << "Enter the Sequence : " << endl;
                for(int i = 0; i < length ;i++)
                    cin >> sss[i];
                    check(sss,choice1);
                if(choice1 == 1)  s11 = new DNA<int>(sss,promoter);
                else if(choice1 == 2) s11 = new RNA<int>(sss,mRNA);
                else if(choice1 == 3) s11 = new Protein<int>(sss);

                 }
                 else if(choice == 2)
                {
                    string ss;
                    cout << "Enter FILE NAME : " << endl;
                    cin >> ss;
                    s11-> load_Sequence(ss);
                }
                else throw notAvailableChoice();

            }
            else if(choice == 2)
            {
                cout << "Enter the file name you want to save to " << endl;
                string ss;
                cin >> ss;
                s11-> save_Sequence(ss);
            }
            else if(choice == 3)
            {
                int str[1000]={0};
                 cout << "Enter the length of the sequence" << endl;
                int length; cin >> length;
                cout << "Enter the Sequence : " << endl;
                for(int i = 0; i < length ;i++)
                    cin >> str[i];
                    check(str,choice1);
                if(choice1 == 1) s22 = new DNA<int>(str,promoter);
                else if(choice1 == 2) s22 = new RNA<int>(str,mRNA);
                else s22 = new Protein<int>(str);
                cout << "the result of align is : " << Align(s11,s22);

            }
            else if(choice == 5) s11->Print();
            else if(choice == 6 )
            {
                 int str[1000]={0};
                 cout << "Enter the length of the sequence" << endl;
                int length; cin >> length;
                cout << "Enter the Sequence : " << endl;
                for(int i = 0; i < length ;i++)
                    cin >> str[i];
                    check(str,choice1);
                if(choice1 == 1) s22 = new DNA<int>(str,promoter);
                else if(choice1 == 2) s22 = new RNA<int>(str,mRNA);
                else s22 = new Protein<int>(str);
                if(s11 == s22) cout << "The sequences are identical " << endl;
                else cout << "The sequences are different " << endl;

            }
            else if(choice == 7)
            {
                int str[1000]={0};
                 cout << "Enter the length of the sequence" << endl;
                int length; cin >> length;
                cout << "Enter the Sequence : " << endl;
                for(int i = 0; i < length ;i++)
                    cin >> str[i];
                    check(str,choice1);
                if(choice1 == 1) s22 = new DNA<int>(str,promoter);
                else if(choice1 == 2) s22 = new RNA<int>(str,mRNA); else s22 = new Protein<int>(str);
                //cout << "The result of adding sequences : " << s11+s22 << endl;
            }
            else if(choice == 8)
            {
                if(choice1 == 1) throw WrongConversion();
                else if(choice1 == 2) cout << static_cast<RNA<int>*>(s11) -> ConvertToDNA() . getSeq() << endl;
                else if(choice1 == 3)
                {
                    int str[1000]={0};
                 cout << "Enter the length of the bigDNA SEQUENCE " << endl;
                int length; cin >> length;
                cout << "Enter the Sequence : " << endl;
                for(int i = 0; i < length ;i++)
                    cin >> str[i];
                    check(str,1);
                    DNA<int> big(str,promoter);
                     DNA<int>* DNAs = ( static_cast<Protein<int>*>(s11) ) -> GetDNAStrandsEncodingMe(big);
                    cout << "The possible DNAs are : " << endl;
                    for(int i = 0;DNAs[i].getEndIndex() != 0;i++)
                        cout << DNAs[i].getSeq() << endl;


                }
                else throw WrongConversion();
            }
            else if(choice == 9)
            {
                if(choice1 == 1) cout << static_cast<DNA<int>*>(s11) -> ConvertToRNA().getSeq() << endl;
                else  throw WrongConversion();

            }
            else if(choice == 10 )
            {
                if(choice1 == 1)
                {
                    RNA<int> a = static_cast<DNA<int>*>(s11) -> ConvertToRNA();
                    cout << " The converted Sequence :  "  << a.ConvertToProtein(CodonsTable()).getSeq() << endl;
                }
                else if(choice1 == 2)
                {
                    cout << "The converted Sequence : " << static_cast<RNA<int>*>(s11) -> ConvertToProtein(CodonsTable()).getSeq() << endl;
                }
                else throw WrongConversion();
            }
            else if(choice == 11) break;


        }
    }
    }
    catch(const strangeCharDNA& a)
    {
       cout<< a.what() ;
    }
    catch(const strangeCharRNA& b)
    {
       cout<< b.what() ;
    }
    catch(const strangeCharProtein& c)
    {
       cout<< c.what() ;
    }
    catch(const wrongDataTypeInput& d)
    {
       cout<< d.what() ;
    }
    catch(const notAvailableChoice& e)
    {
       cout<< e.what();
    }
    catch(...)
    {
            cout << "Wrong operation << please restart the program " << endl;
    }
}
