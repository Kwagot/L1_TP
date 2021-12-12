#include "fish.h"

fish::fish() {
    genus = "None";
    color = "None";
    eat   = "None";
    std::cout << "---------------- deffault constructor of <fish>" << std::endl;
}


fish::fish(std:: string a, std:: string b, std:: string c) {
    genus = a;
    color = b;
    eat   = c;
    std::cout << "---------------- param constructor of <fish>" << std::endl;
}

fish::fish(const fish & obj) {
    this->genus = obj.genus;
    this->color = obj.color;
    this->eat   = obj.eat;
    std::cout << "---------------- copy constructor of <fish>" << std::endl;
}

fish::~fish() {
    std::cout << "---------------- destructor of <fish>" << std::endl;
}


std::string fish::getgenus(){
    return genus;
}

std::string fish::getcolor(){
    return color;
}

std::string fish::geteat(){
    return eat;
}


void fish::setgenus(std::string data){
    this->genus = data;
}

void fish::setcolor(std::string data){
    this->color = data;
}

void fish::seteat(std::string data){
    this->eat = data;
}


void fish::sethome(std::string data){
}

void fish::setFIO(std::string data){
}

void fish::setname(std::string data){
}

std::string fish::gethome(){
    return "None";
}

std::string fish::getFIO(){
    return "None";
}

std::string fish::getname(){
    return "None";
}

char fish::gettype() {
    return type;
}

void fish::show() {
    std::cout << "FISH:\n"
    << "   Genus: " << genus << '\n'
    << "   Color: " << color << '\n'
    << "   Eat:   " << eat   << std::endl;
}

void fish::save(std::ofstream &file, bool bin) {
    if (bin) {

        unsigned int write_offset = 0;

        unsigned int size = genus.length() + color.length() + eat.length() + 4;

        char * byte_array = static_cast<char *>(malloc(sizeof(char) * size));

        memcpy(byte_array+write_offset,&type,1);                        write_offset+=1;
        memcpy(byte_array+write_offset,genus.c_str(),genus.length()+1); write_offset+=genus.length()+1;
        memcpy(byte_array+write_offset,color.c_str(),color.length()+1); write_offset+=color.length()+1;
        memcpy(byte_array+write_offset,eat.c_str(),eat.length()+1);

        file.write(byte_array, size);

        free(byte_array);

        return;
    }

    file << type << '\n';
    file << genus << '\n';
    file << color << '\n';
    file << eat << '\n';
}

void fish::load(std::ifstream &file, bool bin) {
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

        return;
    }

    std::getline(file,genus);
    std::getline(file,color);
    std::getline(file,eat);

}
