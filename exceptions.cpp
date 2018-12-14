#include "exceptions.h"

using namespace std;

const char* strangeCharDNA::what() const throw()
{
    return "Invalid DNA Format,please enter a correct one ";
}

const char* strangeCharRNA::what() const throw()
{
    return "Invalid RNA Format,please enter a correct one ";
}
const char* strangeCharProtein::what() const throw()
{
    return "Invalid Protein Format,please enter a correct one ";
}

const char* wrongDataTypeInput::what() const throw()
{
    return "you have chosen a different dataType, please stick to it";
}

const char* notAvailableChoice::what() const throw()
{
    return "No such choice,please enter your choice according to choices list";
}
const char* WrongConversion::what() const throw()
{
    return "Wrong Conversion operation";
}
