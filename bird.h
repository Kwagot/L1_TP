#ifndef BIRD_H
#define BIRD_H

#include "animal.h"

class bird : public animal {
    public:
        bird();
        bird(std:: string a, std:: string b, std:: string c, std:: string d);
        bird(const bird & obj);
        virtual ~bird();

        virtual std::string getgenus();
        virtual std::string getcolor();
        virtual std::string geteat();
        virtual std::string gethome();


        virtual void setgenus(std::string data);
        virtual void setcolor(std::string data);
        virtual void seteat(std::string data);
        virtual void sethome(std::string data);

        virtual std:: string getFIO();
        virtual void setFIO(std::string data);
        virtual std:: string getname();
        virtual void setname(std::string data);

        virtual void save(std::ofstream & file, bool bin = false);
        virtual void load(std::ifstream & file, bool bin = false);

        virtual void show();

        virtual char gettype();

    private:

        std:: string genus;
        std:: string color;
        std:: string eat;
        std:: string home;

        char type = 'b';

};

#endif // BIRD_H
