#ifndef CAT_H
#define CAT_H

#include "animal.h"

class cat : public animal
{
public:
    cat();
    cat(std:: string a, std:: string b, std:: string c, std:: string d);
    cat(const cat & obg);
    ~cat();

    std:: string genus;
    std:: string color;
    std:: string FIO;
    std:: string name;

    virtual std:: string getgenus();
    virtual std:: string getcolor();
    virtual std:: string getFIO();
    virtual std:: string getname();


    virtual std:: string setgenus();
    virtual std:: string setcolor();
    virtual std:: string setFIO();
    virtual std:: string setname();

    virtual char gettype();

    char type = 'c';
};

#endif // CAT_H
