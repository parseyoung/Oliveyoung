#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

const string DIR_DATABASE = "database/";
const string TEMP_BUFFER = DIR_DATABASE + "temp.csv";

inline const string& getLogPath() {
    static const string LOG = "database/log.txt";
    return LOG;
}

#endif // CONSTANTS_H
