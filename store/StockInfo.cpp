#include "StockInfo.h"

#include <sstream>

using namespace std;

StockInfo::StockInfo()
{
}

StockInfo::StockInfo(const unsigned int quantity, const bool availability = true)
    : mQuantity(quantity)
    , mAvailability(availability)
{
}

const unsigned int StockInfo::getQuantity() const
{
    return mQuantity;
}

const bool StockInfo::isAvailable() const
{
    return mAvailability;
}

void StockInfo::setQuantity(const unsigned int quantity)
{
    mQuantity = quantity;
}

void StockInfo::setAvailability(const bool availability)
{
    mAvailability = availability;
}

const StockInfo StockInfo::createFromString(const std::string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int quantity;
    bool availability;

    // quantity를 파싱
    if (!(iss >> quantity >> comma) || comma != ',') {
        throw invalid_argument("Invalid stock info format (quantity)");
    }

    // availability를 파싱
    if (!(iss >> availability)) {
        throw invalid_argument("Invalid stock info format (availability)");
    }

    return StockInfo(quantity, availability);
}


const string StockInfo::toString() const
{
    return to_string(mQuantity) + "," + to_string(mAvailability);
}
