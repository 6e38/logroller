/*
 * Copyright (c) 2019, Nathan Jenne
 */

#include "fetcharg.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
    FetchArg args(argc, argv);

    cout << "Has -h: " << args.has("-h") << endl;
    cout << "Has --help: " << args.has("--help") << endl;
    cout << "Has an option: " << args.has("an option") << endl;
    cout << "Fetch --name: " << args.fetch("--name", "<empty>") << endl;
    cout << "Fetch -n: " << args.fetch("-n", "<empty>") << endl;
    cout << "Fetch -number: " << args.fetch("-number", "<empty>") << endl;

    return 0;
}

