#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "Purchase.h"

using namespace std;

Purchase::Purchase(unsigned int productId, unsigned int clientId)
    : mProductId(productId)
    , mClientId(clientId)
    , mDate(chrono::system_clock::now())
{
}

Purchase::Purchase(unsigned int productId, unsigned int clientId, const chrono::system_clock::time_point& date)
    : mProductId(productId)
    , mClientId(clientId)
    , mDate(date) 
{
}

const unsigned int Purchase::getProductId() const
{
    return mProductId;
}

const unsigned int Purchase::getClientId() const
{
    return mClientId;
}

const chrono::system_clock::time_point Purchase::getDate() const
{
    return mDate;
}

string Purchase::timePointToString(const chrono::system_clock::time_point& timePoint)
{
    time_t t = chrono::system_clock::to_time_t(timePoint);
    tm tm = *std::localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

chrono::system_clock::time_point Purchase::stringToTimePoint(const string& dateStr) 
{
    tm tm = {};
    istringstream iss(dateStr);
    iss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (iss.fail()) {
        throw std::invalid_argument("Invalid date format");
    }
    std::time_t t = std::mktime(&tm);
    return chrono::system_clock::from_time_t(t);
}

const string Purchase::toString() const 
{
    return to_string(mProductId) + "," + to_string(mClientId) + "," + timePointToString(mDate);
}

const Purchase Purchase::createPurchaseFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int productId;
    unsigned int clientId;
    string date;

    // Parse productId
    if (!(iss >> productId >> comma) || comma != ',') {
        throw invalid_argument("Invalid format for productId");
    }

    // Parse clientId
    if (!(iss >> clientId >> comma) || comma != ',') {
        throw invalid_argument("Invalid format for clientId");
    }

    // Parse date
    if (!getline(iss, date)) {
        throw invalid_argument("Invalid format for date");
    }

    return Purchase(productId, clientId, stringToTimePoint(date));
}
