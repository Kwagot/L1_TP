#include "bird.h"

bird::bird() {
    genus = "None";
    color = "None";
    eat   = "None";
    home  = "None";
    std::cout << "---------------- deffault constructor of <bird>" << std::endl;
}


bird::bird(std::string a, std::string b, std::string c, std::string d) {
    genus = a;
    color = b;
    eat = c;
    home = d;
    std::cout << "---------------- param constructor of <bird>" << std::endl;
}

bird::bird(const bird & obj) {
    this->genus = obj.genus;
    this->color = obj.color;
    this->eat   = obj.eat;
    this->home  = obj.home;
    std::cout << "---------------- copy constructor of <bird>" << std::endl;
}

bird::~bird() {
    std::cout << "---------------- destructor of <bird>" << std::endl;
}

std::string bird::getgenus(){
    return genus;
}

std::string bird::getcolor(){
    return color;
}

std::string bird::geteat(){
    return eat;
}

std::string bird::gethome(){
    return home;
}

void bird::setgenus(std::string data){
    this->genus = data;
}

void bird::setcolor(std::string data){
    this->color = data;
}

void bird::seteat(std::string data){
    this->eat = data;
}

void bird::sethome(std::string data){
    this->home = data;
}

std::string bird::getFIO() {
    return "None";
}

std::string bird::getname() {
    return "None";
}

void bird::setFIO(std::string data) {

}

void bird::setname(std::string data) {

}


char bird::gettype() {
    return type;
}

void bird::show() {
    std::cout << "BIRD:\n"
    << "   Genus: " << genus << '\n'
    << "   Color: " << color << '\n'
    << "   Eat:   " << eat << '\n'
    << "   Home:  " << home << std::endl;
}

void bird::save(std::ofstream &file, bool bin) {
    if (bin) {

        unsigned int write_offset = 0;

        unsigned int size = genus.length() + color.length() + eat.length() + home.length() + 5;

        char * byte_array = static_cast<char *>(malloc(sizeof(char) * size));

        memcpy(byte_array+write_offset,&type,1);                        write_offset+=1;
        memcpy(byte_array+write_offset,genus.c_str(),genus.length()+1); write_offset+=genus.length()+1;
        memcpy(byte_array+write_offset,color.c_str(),color.length()+1); write_offset+=color.length()+1;
        memcpy(byte_array+write_offset,eat.c_str(),eat.length()+1);     write_offset+=eat.length()+1;
        memcpy(byte_array+write_offset,home.c_str(),home.length()+1);

        file.write(byte_array, size);

        free(byte_array);

        return;
    }

    file << type << '\n';
    file << genus << '\n';
    file << color << '\n';
    file << eat << '\n';
    file << home << '\n';
}

void bird::load(std::ifstream &file, bool bin) {
    if (bin) {

        genus = "";
        char read_symbol;
        file.read(&read_symbol,1);
        if (read_symbol == '\0') {
            throw CorruptedFile();
        }

        while (read_symbol != '\0') {
            genus+=read_symbol;
            file.read(&read_symbol,1);
        }


        color = "";
        file.read(&read_symbol,1);
        if (read_symbol == '\0') {
            throw CorruptedFile();
        }

        while (read_symbol != '\0') {
            color+=read_symbol;
            file.read(&read_symbol,1);
        }

        eat = "";
        file.read(&read_symbol,1);
        if (read_symbol == '\0') {
            throw CorruptedFile();
        }

        while (read_symbol != '\0') {
            eat+=read_symbol;
            file.read(&read_symbol,1);
        }

        home = "";
        file.read(&read_symbol,1);
        if (read_symbol == '\0') {
            throw CorruptedFile();
        }

        while (read_symbol != '\0') {
            home+=read_symbol;
            file.read(&read_symbol,1);
        }

        return;
    }

    std::getline(file,genus);
    std::getline(file,color);
    std::getline(file,eat);
    std::getline(file,home);

}
