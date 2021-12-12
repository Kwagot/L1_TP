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
        file << count << '\n';

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

            *classes[i] = *(classes[i+1]);
        }
        //delete container[count-1];
    } else {
        delete classes[0];
    }
    count--;
}

void container::rem(unsigned int id) {
    if (id > 0) {
        if (id > count) {
            std::cout << "ID is out of range" << std::endl;
        } else {
            remove_and_move(id-1);
        }
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
        }
    }
}

