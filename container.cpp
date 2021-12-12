#include "container.h"

container::container() {
    count = 0;
}

container::container(std::string load_path, bool bin) {
    load(load_path,bin);
}

container::container(const container & obj) {
    clean();
    count = obj.count;
    classes = static_cast<animal**>(malloc(sizeof(animal*) * count));

    for (unsigned int i = 0; i < count; ++i) {
        switch (obj.classes[i]->gettype()) {
            case 'b': {
                classes[i] = new bird();
                break;
            }

            case 'c': {
                classes[i] = new cat();
                break;
            }

            case 'f': {
                classes[i] = new fish();
                break;
            }
        }
        *classes[i] = *obj.classes[i];
    }
}

container::~container() {
    clean();
}

void container::clean() {
    if (count > 0) {
        for (unsigned int i = 0; i < count; ++i) {
            delete classes[i];
        }

        count = 0;

        free(classes);

    }
}

void container::load(std::string path, bool bin) {
    char test_byte;
    clean();

    if (bin) {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            throw NoSuchFileOrDirectory();
        }
        file.read(&test_byte,1);
        if (test_byte != 1) {
            file.close();
            throw WrongFileFormat();
        }
        file.read((char*)&count,4);
        if (count <= 0) throw IncorrectDataParam();

        classes = static_cast<animal**>(malloc(sizeof(animal*) * count));

        for (unsigned int i = 0; i < count; ++i) {
            file.read(&test_byte, 1);

            switch (test_byte) {
                case 'b': {
                    classes[i] = new bird();
                    break;
                }

                case 'c': {
                    classes[i] = new cat();
                    break;
                }

                case 'f': {
                    classes[i] = new fish();
                    break;
                }
                default: {
                    throw CorruptedFile();
                }
            }

            classes[i]->load(file,bin);
        }

        file.close();

    } else {
        std::ifstream file(path, std::ios::in);
        if (!file.is_open()) {
            throw NoSuchFileOrDirectory();
        }
        file.read(&test_byte,1);
        if (test_byte != '1') {
            file.close();
            throw WrongFileFormat();
        }
        // skips \n
        file.read(&test_byte,1);


        std::string line;

        std::getline(file,line);

        try {
            count = std::stoi(line);
        }  catch (std::invalid_argument) {
            throw CorruptedFile();
        }

        classes = static_cast<animal**>(malloc(sizeof(animal*) * count));

        for (unsigned int i = 0; i < count; ++i) {

            std::getline(file,line);

            switch (line[0]) {
                case 'b': {
                    classes[i] = new bird();
                    break;
                }

                case 'c': {
                    classes[i] = new cat();
                    break;
                }

                case 'f': {
                    classes[i] = new fish();
                    break;
                }
                default: {
                    throw CorruptedFile();
                }
            }

            classes[i]->load(file,bin);
        }

        file.close();
    }
}

void container::save(std::string path, bool bin) {
    if (bin) {
        std::ofstream file (path, std::ios::out | std::ios::binary);
        char typeflag = 1;
        file.write(&typeflag,1);
        file.write((char*)&count,4);

        for (unsigned int i = 0; i < count; ++i) {
            classes[i]->save(file,bin);
        }

    } else {
        std::ofstream file (path, std::ios::out);
        char typeflag = '1';
        file.write(&typeflag,1);
        file << '\n' << count << '\n';

        for (unsigned int i = 0; i < count; ++i) {
            classes[i]->save(file,bin);
        }
    }
}

void container::add(bird &obj) {
    if (classes) {
        classes = static_cast<animal **>(realloc(classes, (count+1) * sizeof(animal*)));
    } else {
        classes = static_cast<animal **>(malloc(sizeof(animal*)));
    }
    classes[count++] = new bird(obj);
}

void container::add(cat &obj) {
    if (classes) {
        classes = static_cast<animal **>(realloc(classes, (count+1) * sizeof(animal*)));
    } else {
        classes = static_cast<animal **>(malloc(sizeof(animal*)));
    }
    classes[count++] = new cat(obj);
}

void container::add(fish &obj) {
    if (classes) {
        classes = static_cast<animal **>(realloc(classes, (count+1) * sizeof(animal*)));
    } else {
        classes = static_cast<animal **>(malloc(sizeof(animal*)));
    }
    classes[count++] = new fish(obj);
}

void container::remove_and_move(unsigned int id) {
    if (count > 1) {
        for (unsigned int  i = id; i < count-1; ++i) {
            delete classes[i];

            switch (classes[i+1]->gettype()) {
                case 'b': {
                    classes[i] = new bird();

                    classes[i]->setgenus(classes[i+1]->getgenus());
                    classes[i]->setcolor(classes[i+1]->getcolor());
                    classes[i]->seteat(classes[i+1]->geteat());
                    classes[i]->sethome(classes[i+1]->gethome());

                    break;
                }

                case 'c': {
                    classes[i] = new cat();

                    classes[i]->setgenus(classes[i+1]->getgenus());
                    classes[i]->setcolor(classes[i+1]->getcolor());
                    classes[i]->setFIO(classes[i+1]->getFIO());
                    classes[i]->setname(classes[i+1]->getname());

                    break;
                }

                case 'f': {
                    classes[i] = new fish();

                    classes[i]->setgenus(classes[i+1]->getgenus());
                    classes[i]->setcolor(classes[i+1]->getcolor());
                    classes[i]->seteat(classes[i+1]->geteat());

                    break;
                }
            }
        }
        delete classes[count - 1];
        //delete container[count-1];
    } else {
        delete classes[0];
    }
    count--;
}

void container::rem(unsigned int id) {
    if (id > count) {
        std::cout << "ID is out of range" << std::endl;
    } else {
        remove_and_move(id-1);
    }
}

void container::show(unsigned int id) {

    if (count == 0) {
        std::cout << "List is empty";
    }

    if (id > 0) {
        id--;
        if (id >= count) {
            std::cout << "ID is out of range" << std::endl;
        } else {
            classes[id]->show();
            return;
        }
    }

    for (int i = 0; i < count; ++i) {
        classes[i]->show();
    }
}

void container::show_menu() {
    int run = true;
    int pos = 0;

    std::string command;
    std::size_t next_char;

    int command_num;
    float command_float;

    int command_char;

    std::string path;

    std::string genus;
    std::string color;
    std::string eat;
    std::string home;
    std::string FIO;
    std::string name;

    bird tmp_bird;
    cat  tmp_cat;
    fish tmp_fish;

    bool show_bird;
    bool show_cat;
    bool show_fish;

    std::string bird_filter[4] = {"_","_","_","_"};
    std::string cat_filter [4] = {"_","_","_","_"};
    std::string fish_filter[3] = {"_","_","_"};

    bool showed;

    while(run) {

        std::cout << '\n' << std::endl;

        for(int i = 0; i < menu_count; ++i) {
            std::cout << i << "   " << menu[i] << '\n';
        }

        command_num = -1;
        while (command_num < 0) {

            std::cout << "Command -> ";
            std::cin  >> command;

            try {
                command_num = std::stoi(command,&next_char);
            }  catch (std::invalid_argument) {
                std::cout << "Not correct argument\n";
            }
        }

        switch (command_num) {
            case 0: {
                command_num = -1;
                while (command_num < 0) {

                    std::cout << " ID (0 for all) -> ";
                    std::cin  >> command;

                    try {
                        command_num = std::stoi(command,&next_char);
                    }  catch (std::invalid_argument) {
                        std::cout << "ID not in range\n";
                    }

                    if (command_num < 0 || command_num > count) command_num = -1;
                }

                show(command_num);

                break;
            }
            case 1: {

                command = "";

                std::cout << " CLASS RESTRICTIONS \n";

                while (command != "y" && command != "n") {
                    std::cout << "    SHOW BIRD (y/n) -> ";
                    std::cin  >> command;
                }

                show_bird = false;
                if (command[0] == 'y') show_bird = true;

                command = "";
                while (command != "y" && command != "n") {
                    std::cout << "    SHOW CAT  (y/n) -> ";
                    std::cin  >> command;
                }

                show_cat = false;
                if (command[0] == 'y') show_cat = true;

                command = "";
                while (command != "y" && command != "n") {
                    std::cout << "    SHOW FISH (y/n) -> ";
                    std::cin  >> command;
                }

                show_fish = false;
                if (command[0] == 'y') show_fish = true;

                std::cout << " PER PARAM RESTRICTIONS \n";
                std::cout << " < _ > for no restriction \n";

                if (show_bird) {
                    std::cout << "\n    BIRD \n";
                    std::cout << "    Genus -> ";
                    std::cin  >> bird_filter[0];

                    std::cout << "    Color -> ";
                    std::cin  >> bird_filter[1];

                    std::cout << "    Eat   -> ";
                    std::cin  >> bird_filter[2];

                    std::cout << "    Home  -> ";
                    std::cin  >> bird_filter[3];
                }

                if (show_cat) {
                    std::cout << "\n    CAT  \n";
                    std::cout << "    Genus -> ";
                    std::cin  >> cat_filter[0];

                    std::cout << "    Color -> ";
                    std::cin  >> cat_filter[1];

                    std::cout << "    FIO   -> ";
                    std::cin  >> cat_filter[2];

                    std::cout << "    Name  -> ";
                    std::cin  >> cat_filter[3];
                }

                if (show_fish) {
                    std::cout << "\n    FISH \n";
                    std::cout << "    Genus -> ";
                    std::cin  >> cat_filter[0];

                    std::cout << "    Color -> ";
                    std::cin  >> cat_filter[1];

                    std::cout << "    Eat   -> ";
                    std::cin  >> cat_filter[2];
                }

                std::cout << '\n';

                showed = true;
                for (int i = 0; i < count; ++i) {
                    switch (classes[i]->gettype()) {
                        case 'b': {

                            if (show_bird) {
                                if (bird_filter[0][0] != '_') {
                                    if (bird_filter[0] != classes[i]->getgenus()) continue;
                                }
                                if (bird_filter[1][0] != '_') {
                                    if (bird_filter[1] != classes[i]->getcolor()) continue;
                                }
                                if (bird_filter[2][0] != '_') {
                                    if (bird_filter[2] != classes[i]->geteat()) continue;
                                }
                                if (bird_filter[3][0] != '_') {
                                    if (bird_filter[3] != classes[i]->gethome()) continue;
                                }

                                showed = false;

                                classes[i]->show();
                            }

                            break;
                        }

                        case 'c': {

                            if (show_cat) {
                                if (cat_filter[0][0] != '_') {
                                    if (cat_filter[0] != classes[i]->getgenus()) continue;
                                }
                                if (cat_filter[1][0] != '_') {
                                    if (cat_filter[1] != classes[i]->getcolor()) continue;
                                }
                                if (cat_filter[2][0] != '_') {
                                    if (cat_filter[2] != classes[i]->getFIO()) continue;
                                }
                                if (cat_filter[3][0] != '_') {
                                    if (cat_filter[3] != classes[i]->getname()) continue;
                                }

                                showed = false;

                                classes[i]->show();
                            }

                            break;
                        }

                        case 'f': {

                            if (show_fish) {
                                if (fish_filter[0][0] != '_') {
                                    if (fish_filter[0] != classes[i]->getgenus()) continue;
                                }
                                if (fish_filter[1][0] != '_') {
                                    if (fish_filter[1] != classes[i]->getcolor()) continue;
                                }
                                if (fish_filter[2][0] != '_') {
                                    if (fish_filter[2] != classes[i]->geteat()) continue;
                                }

                                showed = false;

                                classes[i]->show();
                            }

                            break;
                        }
                    }
                }

                if (showed) {
                    std::cout << "No classes that mach current filter\n";
                }


                break;
            }
            case 2: {

                command_num = -1;
                while (command_num <= 0) {

                    std::cout << " ID -> ";
                    std::cin  >> command;

                    try {
                        command_num = std::stoi(command,&next_char);
                    }  catch (std::invalid_argument) {
                        std::cout << "ID not in range\n";
                    }

                    if (command_num <= 0 || command_num > count) command_num = -1;
                }

                command = " Editing class ";

                switch (classes[command_num-1]->gettype()) {
                    case 'b': {
                        command += "Bird ";
                        break;
                    }

                    case 'c': {
                        command += "Cat ";
                        break;
                    }

                    case 'f': {
                        command += "Fish ";
                        break;
                    }
                }

                command += "at pos " + std::to_string(command_num-1);
                std::cout << command << "\n";
                show(command_num);

                switch (classes[command_num-1]->gettype()) {
                    case 'b': {
                        std::cout << " Genus -> ";
                        std::cin  >> genus;

                        std::cout << " Color -> ";
                        std::cin  >> color;

                        std::cout << " Eat   -> ";
                        std::cin  >> eat;

                        std::cout << " Home  -> ";
                        std::cin  >> home;

                        classes[command_num-1]->setgenus(genus);
                        classes[command_num-1]->setcolor(color);
                        classes[command_num-1]->seteat(eat);
                        classes[command_num-1]->sethome(home);
                        break;
                    }

                    case 'c': {
                        std::cout << " Genus -> ";
                        std::cin  >> genus;

                        std::cout << " Color -> ";
                        std::cin  >> color;

                        std::cout << " FIO   -> ";
                        std::cin  >> FIO;

                        std::cout << " Name  -> ";
                        std::cin  >> name;

                        classes[command_num-1]->setgenus(genus);
                        classes[command_num-1]->setcolor(color);
                        classes[command_num-1]->setFIO(FIO);
                        classes[command_num-1]->setname(name);
                        break;
                    }

                    case 'f': {
                        std::cout << " Genus -> ";
                        std::cin  >> genus;

                        std::cout << " Color -> ";
                        std::cin  >> color;

                        std::cout << " Eat   -> ";
                        std::cin  >> eat;

                        classes[command_num-1]->setgenus(genus);
                        classes[command_num-1]->setcolor(color);
                        classes[command_num-1]->seteat(eat);
                        break;
                    }
                }

                break;
            }
            case 3: {

                command = " ";
                while (true) {

                    std::cout << " Select class (Bird/Cat/Fish) -> ";
                    std::cin  >> command;

                    if (command[0] == 'b' || command[0] == 'B' ||
                        command[0] == 'c' || command[0] == 'C' ||
                        command[0] == 'f' || command[0] == 'F') break;

                    std::cout << "No such class\n";
                }

                if (command[0] < 97) command[0]+=32;

                switch (command[0]) {
                    case 'b': {
                        std::cout << " Genus -> ";
                        std::cin  >> genus;

                        std::cout << " Color -> ";
                        std::cin  >> color;

                        std::cout << " Eat   -> ";
                        std::cin  >> eat;

                        std::cout << " Home  -> ";
                        std::cin  >> home;

                        tmp_bird = bird(genus,color,eat,home);

                        add(tmp_bird);
                        break;
                    }

                    case 'c': {
                        std::cout << " Genus -> ";
                        std::cin  >> genus;

                        std::cout << " Color -> ";
                        std::cin  >> color;

                        std::cout << " FIO   -> ";
                        std::cin  >> FIO;

                        std::cout << " Name  -> ";
                        std::cin  >> name;

                        tmp_cat = cat(genus,color,FIO,name);

                        add(tmp_cat);
                        break;
                    }

                    case 'f': {
                        std::cout << " Genus -> ";
                        std::cin  >> genus;

                        std::cout << " Color -> ";
                        std::cin  >> color;

                        std::cout << " Eat   -> ";
                        std::cin  >> eat;

                        tmp_fish = fish(genus,color,eat);

                        add(tmp_fish);
                        break;
                    }
                }

                break;
            }


            case 4: {
                command_num = -1;

                if (count == 0) { std::cout << "List is empty\n"; break; }

                while (command_num < 0) {

                    std::cout << " ID -> ";
                    std::cin  >> command;

                    try {
                        command_num = std::stoi(command,&next_char);
                    }  catch (std::invalid_argument) {
                        std::cout << "ID not in range\n";
                    }

                    if (command_num < 0 || command_num > count) command_num = -1;
                }

                show(command_num);
                rem(command_num);

                break;
            }

            case 5: {

                command = "";

                while (command != "bin" && command != "txt") {
                    std::cout << " TYPE (bin/txt) -> ";
                    std::cin >> command;
                }

                command_num = false;
                if (command == "bin") command_num = true;

                std::cout << " FILE PATH -> ";
                std::cin >> command;

                save(command, command_num);

                break;
            }

            case 6: {

                command = "";

                while (command != "bin" && command != "txt") {
                    std::cout << " TYPE (bin/txt) -> ";
                    std::cin >> command;
                }

                command_num = false;
                if (command == "bin") command_num = true;

                std::cout << " FILE PATH -> ";
                std::cin >> command;

                load(command, command_num);

                break;
            }

            case 7: {
                run = false;
                break;
            }

        }
    }
}

