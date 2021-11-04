#include "bird.h"

bird::bird()
{

}


bird::bird(std:: string a, std:: string b, std:: string c, std:: string d)
{
    genus = a;
    color = b;
    eat = c;
    home = d;
}

std::string bird::getgenus(){
    return genus;
}

std::string bird::getcolor(){
    return color;
}

std::string bird::geteat(){
    return eat;
}

std::string bird::gethome(){
    return home;
}

std::string bird::setgenus(){
    return genus;
}

std::string bird::setcolor(){
    return color;
}

std::string bird::seteat(){
    return eat;
}

std::string bird::sethome(){
    return home;
}
