#ifndef FISH_H
#define FISH_H

#include "animal.h"

class fish : public animal
{
public:
    fish();
    fish(std:: string a, std:: string b, std:: string c);
    fish(const fish & obg);
    ~fish();

    std:: string genus;
    std:: string color;
    std:: string eat;

    virtual std:: string getgenus();
    virtual std:: string getcolor();
    virtual std:: string geteat();

    virtual std:: string setgenus();
    virtual std:: string setcolor();
    virtual std:: string seteat();

    virtual char gettype();

    char type = 'f';
};

#endif // FISH_H
