#ifndef CAT_H
#define CAT_H

#include "animal.h"

class cat : public animal {
    public:
        cat();
        cat(std:: string a, std:: string b, std:: string c, std:: string d);
        cat(const cat & obg);
        virtual ~cat();

        virtual std:: string getgenus();
        virtual std:: string getcolor();
        virtual std:: string getFIO();
        virtual std:: string getname();


        virtual void setgenus(std::string data);
        virtual void setcolor(std::string data);
        virtual void setFIO(std::string data);
        virtual void setname(std::string data);

        virtual std:: string geteat();
        virtual std:: string gethome();
        virtual void seteat(std::string data);
        virtual void sethome(std::string data);

        virtual void save(std::ofstream & file, bool bin = false);
        virtual void load(std::ifstream & file, bool bin = false);

        virtual void show();

    private:

        std:: string genus;
        std:: string color;
        std:: string FIO;
        std:: string name;

        char type = 'c';
};

#endif // CAT_H
