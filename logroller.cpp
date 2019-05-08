/*
 * Copyright (c) 2019, Nathan Jenne
 */

#include "logroller.h"
#include "fetcharg.h"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;


const string LogRoller::DefaultFilename("Log");

const unsigned int LogRoller::DefaultFileLen = 500'000;
const unsigned int LogRoller::MaxFileLen = 2'000'000'000;
const unsigned int LogRoller::MinFileLen = 1'000;

const int LogRoller::DefaultLogCount = 10;
const int LogRoller::MaxLogCount = 100;
const int LogRoller::MinLogCount = 1;

const char* LogRoller::TimeFormat = "[%F %T]: ";

LogRoller::LogRoller(string filename, unsigned int fileLen, int logCount, bool quiet)
{
    this->filename = (filename.length() > 0) ? filename : DefaultFilename;
    this->filename.append(".log");

    path = getPath();

    this->fileLen = (fileLen >= MinFileLen && fileLen <= MaxFileLen) ? fileLen : DefaultFileLen;

    this->logCount = (logCount >= MinLogCount && logCount <= MaxLogCount) ? logCount : DefaultLogCount;

    if (!quiet)
    {
        cout << "Logging to " << this->filename << ", "
            << this->fileLen << " bytes, "
            << this->logCount << " files" << endl;
    }
}

void LogRoller::log()
{
    while (true)
    {
        string s;
        getline(cin, s);
        if (cin.eof())
        {
            break;
        }
        logLine(s);
    }
    file.close();
}

void LogRoller::logLine(const string line)
{
    time_t t = time(nullptr);
    tm tm = {};
    localtime_r(&t, &tm);

    unsigned int bytes = 0;
    char buffer[100] = {};
    bytes += strftime(buffer, sizeof(buffer), TimeFormat, &tm);
    bytes += line.length() + 1;

    rollFile(bytes);

    file << buffer << line << '\n';
    file.flush();
}

void LogRoller::rollFile(unsigned int bytes)
{
    if (file.is_open())
    {
        if ((unsigned int)file.tellp() + bytes >= fileLen)
        {
            file.close();
            moveFiles();
        }
    }

    if (!file.is_open())
    {
        file.open(filename, ios_base::app);  // TODO check for failure
    }
}

void LogRoller::moveFiles()
{
    char buf_to[100];
    char buf_from[100];
    const char* c_name = filename.c_str();
    for (int i = logCount - 2; i > 0; i--)
    {
        snprintf(buf_from, sizeof(buf_from), "%s.%d", c_name, i);
        snprintf(buf_to, sizeof(buf_to), "%s.%d", c_name, i + 1);
        (void)rename(buf_from, buf_to);
    }
    snprintf(buf_to, sizeof(buf_to), "%s.1", c_name);
    (void)rename(c_name, buf_to);
}

string LogRoller::getPath()
{
    size_t i = 0;
    i = filename.find_last_of("/\\");
    if (i == filename.npos)
    {
        return ".";
    }
    else
    {
        return filename.substr(0, i);
    }
}

int main(int argc, char* argv[])
{
    FetchArg args(argc, argv);

    if (args.has("-h") || args.has("--help"))
    {
        cout << endl
            << "Usage: " << argv[0] << " [-f <log file>] [-b <max bytes>] [-l <# of log files>] [-q]" << endl
            << endl
            << "    -f <log file>       Prefix for log file name. Default is 'Log'." << endl
            << "    -b <max bytes>      Max log file size in bytes. Default is 1,000,000." << endl
            << "    -l <# of log files> Max number of log files to keep. Default is 10." << endl
            << "    -q                  Quiet mode, no output. Default is not quiet." << endl
            << "    -h,--help           Display this help message and exit." << endl
            << endl;
        return 0;
    }

    string filename = args.fetch("-f", "");

    int n = stoi(args.fetch("-b", "0"));

    int c = stoi(args.fetch("-l", "0"));

    bool q = args.has("-q");

    LogRoller logRoller(filename, n, c, q);
    logRoller.log();

    return 0;
}

