#ifndef FISH_H
#define FISH_H

#include "animal.h"

class fish : public animal {
    public:
        fish();
        fish(std:: string a, std:: string b, std:: string c);
        fish(const fish & obg);
        virtual ~fish();

        virtual std:: string getgenus();
        virtual std:: string getcolor();
        virtual std:: string geteat();

        virtual void setgenus(std::string data);
        virtual void setcolor(std::string data);
        virtual void seteat(std::string data);

        virtual void sethome(std::string data);
        virtual void setFIO(std::string data);
        virtual std:: string gethome();
        virtual std:: string getFIO();


        virtual void save(std::ofstream & file, bool bin = false);
        virtual void load(std::ifstream & file, bool bin = false);

        virtual void show();

    private:
        std:: string genus;
        std:: string color;
        std:: string eat;

        char type = 'f';
};

#endif // FISH_H
