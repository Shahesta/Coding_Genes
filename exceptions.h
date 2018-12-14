#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
using namespace std;
class  strangeCharDNA  : public exception
{
public:
   virtual const char* what() const throw();

};

class  strangeCharRNA : public exception
{
public:
   virtual const char* what() const throw();

};

class strangeCharProtein : public exception
{
public:
   virtual const char* what() const throw();
};

class wrongDataTypeInput : public exception
{
public:
   virtual const char* what() const throw();
};

class  notAvailableChoice : public exception
{
public:
   virtual const char* what() const throw();
};

class WrongConversion : public exception
{
public:
   virtual const char* what() const throw();
};
#endif // EXCEPTIONS_H
