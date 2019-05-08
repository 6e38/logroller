/*
 * Copyright (c) 2019, Nathan Jenne
 */

#include "fetcharg.h"

using namespace std;


FetchArg::FetchArg(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        args.emplace_back(argv[i]);
    }
}

string FetchArg::fetch(string name, string defaultValue)
{
    bool found = false;
    for (string s : args)
    {
        if (found)
        {
            return s;
        }
        else if (s == name)
        {
            found = true;
        }
        else
        {
            auto iter = mismatch(name.begin(), name.end(), s.begin());
            if (iter.first == name.end())
            {
                size_t i = s.find_first_of('=');
                if (i != s.npos)
                {
                    return s.substr(i + 1, s.npos);
                }
            }
        }
    }
    return defaultValue;
}

bool FetchArg::has(string name)
{
    for (string s : args)
    {
        if (s == name)
        {
            return true;
        }
    }
    return false;
}

