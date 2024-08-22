#include <assert.h>
#include <chrono>
#include <ctime>

#include "Logger.h"
#include "../database/Constants.h"

Logger::Logger(const string& className)
    : mClassName(className) 
{
    mLogFile.open(LOG, ios::app);
    if (!mLogFile.is_open()) {
        cerr << "Error opening log file: " << LOG << endl;
    }
}

Logger::~Logger() 
{
    if (mLogFile.is_open()) {
        mLogFile.close();
    }
}

string Logger::logLevelToString(LogLevel level) 
{
    switch (level) {
        case DEBUG: 
            return "DEBUG";
        case INFO: 
            return "INFO";
        case WARNING: 
            return "WARNING";
        case ERROR: 
            return "ERROR";
        default:
            assert(false);
            return "UNKNOWN";
    }
}

void Logger::info(const string& message) 
{
    log(INFO, message);
}

void Logger::debug(const string& message) 
{
    log(DEBUG, message);
}

void Logger::warning(const string& message) 
{
    log(WARNING, message);
}

void Logger::error(const string& message) 
{
    log(ERROR, message);
}

void Logger::log(const LogLevel& level, const string& message) 
{
    string logMessage = getTimestamp() + " [" + logLevelToString(level) + "] " + mClassName + ": " + message;

    if (mLogFile.is_open()) {
        mLogFile << logMessage << endl;
    }
    cout << logMessage << endl;
}

string Logger::getTimestamp() 
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now_time));
    return string(buffer);
}


