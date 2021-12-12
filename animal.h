#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>
#include <fstream>

#include <exceptions.h>

class animal {
    public:

        virtual ~animal();

        virtual std:: string getgenus() = 0;
        virtual std:: string getcolor() = 0;
        virtual std:: string geteat() = 0;
        virtual std:: string gethome() = 0;
        virtual std:: string getFIO() = 0;

        virtual void setgenus(std::string data) = 0;
        virtual void setcolor(std::string data) = 0;
        virtual void seteat(std::string data)   = 0;
        virtual void sethome(std::string data)  = 0;
        virtual void setFIO(std::string data)   = 0;

        virtual void save(std::ofstream & file, bool bin = false) = 0;
        virtual void load(std::ifstream & file, bool bin = false) = 0;

        virtual void show() = 0;

        char gettype();

    private:
        char type = 'n';
};

#endif // ANIMAL_H
