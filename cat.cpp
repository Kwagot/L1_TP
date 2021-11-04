#include "cat.h"

cat::cat()
{

}

cat::cat(std:: string a, std:: string b, std:: string c, std:: string d)
{
    genus = a;
    color = b;
    FIO = c;
    name = d;
}

std::string cat::getgenus(){
    return genus;
}

std::string cat::getcolor(){
    return color;
}

std::string cat::getFIO(){
    return FIO;
}

std::string cat::getname(){
    return name;
}

std::string cat::setgenus(){
    return genus;
}

std::string cat::setcolor(){
    return color;
}

std::string cat::setFIO(){
    return FIO;
}

std::string cat::setname(){
    return name;
}
