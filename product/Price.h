#ifndef PRICE_H
#define PRICE_H

#include <stdexcept>

class Price {
public:
    Price(unsigned int price) {
        if (price < 0) {
            throw std::invalid_argument("Price cannot be negative.");
        }
        mPrice = price;
    }

    unsigned int get() const {
        return mPrice;
    }

private:
    unsigned int mPrice;
};

#endif // PRICE_H
