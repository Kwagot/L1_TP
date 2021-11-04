#ifndef BIRD_H
#define BIRD_H

#include "animal.h"

class bird : public animal
{
public:
    bird();
    bird(std:: string a, std:: string b, std:: string c, std:: string d);
    bird(const bird & obg);
    ~bird();

    std:: string genus;
    std:: string color;
    std:: string eat;
    std:: string home;


    virtual std:: string getgenus();
    virtual std:: string getcolor();
    virtual std:: string geteat();
    virtual std:: string gethome();


    virtual std:: string setgenus();
    virtual std:: string setcolor();
    virtual std:: string seteat();
    virtual std:: string sethome();

    virtual char gettype();

    char type = 'b';

};

#endif // BIRD_H
