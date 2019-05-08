/*
 * Copyright (c) 2019, Nathan Jenne
 */

#ifndef LOGROLLER_H
#define LOGROLLER_H

#include <fstream>
#include <string>


class LogRoller
{

public:
    LogRoller(std::string filename, unsigned int fileLen, int logCount, bool quiet);
    void log();

private:
    static const std::string DefaultFilename;
    static const unsigned int DefaultFileLen;
    static const unsigned int MaxFileLen;
    static const unsigned int MinFileLen;
    static const int DefaultLogCount;
    static const int MaxLogCount;
    static const int MinLogCount;
    static const char* TimeFormat;

    std::ofstream file;
    std::string filename;
    std::string path;
    int logCount;
    unsigned int fileLen;

    void logLine(const std::string line);
    void rollFile(unsigned int bytes);
    void moveFiles();
    std::string getPath();

};

#endif

