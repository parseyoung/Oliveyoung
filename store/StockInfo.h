#ifndef STOCK_INFO_H
#define STOCK_INFO_H

#include <string>

using namespace std;

class StockInfo
{
public:
    StockInfo(); // for stl
    StockInfo(const unsigned int quantity, const bool availability);

    const unsigned int getQuantity() const;
    const bool isAvailable() const;

    void setQuantity(const unsigned int quantity);
    void setAvailability(const bool availability);

    static const StockInfo createFromString(const string& str);
    const string toString() const;

private:
    unsigned int mQuantity;
    bool mAvailability;
};

#endif // STOCK_INFO_H
