#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

struct WrongFileFormat : public std::exception {
    const char * what () const throw () {
        return "Wrong file format";
    }
};

struct NoSuchFileOrDirectory : public std::exception {
    const char * what () const throw () {
        return "No such file or directory";
    }
};

struct IncorrectDataParam : public std::exception {
    const char * what () const throw () {
        return "File data param is wrong";
    }
};

struct CorruptedFile : public std::exception {
    const char * what () const throw () {
        return "File is broken, too short or some data is missing";
    }
};

#endif // EXCEPTIONS_H
