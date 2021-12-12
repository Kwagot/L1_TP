#include "cat.h"

cat::cat() {
    genus = "None";
    color = "None";
    FIO   = "None";
    name  = "None";
    std::cout << "---------------- deffault constructor of <cat>" << std::endl;
}

cat::cat(std:: string a, std:: string b, std:: string c, std:: string d) {
    genus = a;
    color = b;
    FIO   = c;
    name  = d;
    std::cout << "---------------- param constructor of <cat>" << std::endl;
}

cat::cat(const cat & obj) {
    this->genus = obj.genus;
    this->color = obj.color;
    this->FIO   = obj.FIO;
    this->name  = obj.name;
    std::cout << "---------------- copy constructor of <cat>" << std::endl;
}

cat::~cat() {
    std::cout << "---------------- destructor of <cat>" << std::endl;
}

std::string cat::getgenus(){
    return genus;
}

std::string cat::getcolor(){
    return color;
}

std::string cat::getFIO(){
    return FIO;
}

std::string cat::getname(){
    return name;
}

void cat::setgenus(std::string data){
    this->genus = data;
}

void cat::setcolor(std::string data){
    this->color = data;
}

void cat::setFIO(std::string data){
    this->FIO = data;
}

void cat::setname(std::string data){
    this->name = data;
}

void cat::seteat(std::string data){
}

void cat::sethome(std::string data){
}

std::string cat::geteat(){
    return "None";
}

std::string cat::gethome(){
    return "None";
}

char cat::gettype() {
    return type;
}

void cat::show() {
    std::cout << "CAT:\n"
    << "   Genus: " << genus << '\n'
    << "   Color: " << color << '\n'
    << "   FIO:   " << FIO << '\n'
    << "   Name:  " << name << std::endl;
}

void cat::save(std::ofstream &file, bool bin) {
    if (bin) {

        unsigned int write_offset = 0;

        unsigned int size = genus.length() + color.length() + FIO.length() + name.length() + 5;

        char * byte_array = static_cast<char *>(malloc(sizeof(char) * size));

        memcpy(byte_array+write_offset,&type,1);                        write_offset+=1;
        memcpy(byte_array+write_offset,genus.c_str(),genus.length()+1); write_offset+=genus.length()+1;
        memcpy(byte_array+write_offset,color.c_str(),color.length()+1); write_offset+=color.length()+1;
        memcpy(byte_array+write_offset,FIO.c_str(),FIO.length()+1);     write_offset+=FIO.length()+1;
        memcpy(byte_array+write_offset,name.c_str(),name.length()+1);

        file.write(byte_array, size);

        free(byte_array);

        return;
    }

    file << type << '\n';
    file << genus << '\n';
    file << color << '\n';
    file << FIO << '\n';
    file << name << '\n';
}

void cat::load(std::ifstream &file, bool bin) {
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

        FIO = "";
        file.read(&read_symbol,1);
        if (read_symbol == '\0') {
            throw CorruptedFile();
        }

        while (read_symbol != '\0') {
            FIO+=read_symbol;
            file.read(&read_symbol,1);
        }

        name = "";
        file.read(&read_symbol,1);
        if (read_symbol == '\0') {
            throw CorruptedFile();
        }

        while (read_symbol != '\0') {
            name+=read_symbol;
            file.read(&read_symbol,1);
        }

        return;
    }

    std::getline(file,genus);
    std::getline(file,color);
    std::getline(file,FIO);
    std::getline(file,name);

}
