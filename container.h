#ifndef CONTAINER_H
#define CONTAINER_H

#include <animal.h>
#include <bird.h>
#include <cat.h>
#include <fish.h>

#include <string>
#include <fstream>
#include <iostream>

class container {
    public:
        container();
        container(std::string load_path, bool bin = true);
        container(const container & obj);
        ~container();

        void    show(unsigned int id);
        void    load(std::string path, bool bin = false);
        void    save(std::string path, bool bin = false);

        void    add(bird & obj);
        void    add(cat  & obj);
        void    add(fish & obj);

        void    rem(unsigned int id);

        void    show_menu();

    private:

        void    clean();
        void    remove_and_move(unsigned int id);

        animal ** classes = nullptr;
        unsigned int count = 0;

        std::string menu[8] = {
            "Show",
            "Show with params",
            "Select/Edit",
            "Add",
            "Remove",
            "Save",
            "Load",
            "Exit"
        };

        int menu_count = 8;
};

#endif // CONTAINER_H
