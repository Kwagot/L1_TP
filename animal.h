#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

class animal
{
public:

    virtual std:: string getgenus() = 0;
    virtual std:: string getcolor() = 0;
    virtual std:: string geteat() = 0;
    virtual std:: string gethome() = 0;
    virtual std:: string getFIO() = 0;

    virtual std:: string setgenus() = 0;
    virtual std:: string setcolor() = 0;
    virtual std:: string seteat() = 0;
    virtual std:: string sethome() = 0;
    virtual std:: string setFIO() = 0;
    virtual char gettype() = 0;
};

#endif // ANIMAL_H
