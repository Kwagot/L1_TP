#include "fish.h"

fish::fish()
{

}


fish::fish(std:: string a, std:: string b, std:: string c)
{
    genus = a;
    color = b;
    eat = c;
}

std::string fish::getgenus(){
    return genus;
}

std::string fish::getcolor(){
    return color;
}

std::string fish::geteat(){
    return eat;
}


std::string fish::setgenus(){
    return genus;
}

std::string fish::setcolor(){
    return color;
}

std::string fish::seteat(){
    return eat;
}
