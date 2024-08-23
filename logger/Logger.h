#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

using namespace std;

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(const string& className);
    ~Logger();

    void info(const string& message);
    void debug(const string& message);
    void warning(const string& message);
    void error(const string& message);

private:
    string logLevelToString(LogLevel level);
    void log(const LogLevel& level, const string& message);
    string getTimestamp();

    string mClassName;
    ofstream mLogFile;
};

#endif // LOGGER_H
