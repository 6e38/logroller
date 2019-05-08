/*
 * Copyright (c) 2019, Nathan Jenne
 */

#ifndef FETCHARG_H
#define FETCHARG_H

#include <list>
#include <string>

class FetchArg
{

public:
    FetchArg(int argc, char* argv[]);
    std::string fetch(std::string name, std::string defaultValue);
    bool has(std::string name);

private:
    std::list<std::string> args;

};

#endif

