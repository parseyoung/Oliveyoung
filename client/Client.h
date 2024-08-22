#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "Name.h"
#include "PhoneNumber.h"
#include "Point.h"

using namespace std;

class Client
{
public:
    Client(unsigned int id, const Name name, const PhoneNumber phoneNumber, const Point point);
    ~Client();
    bool operator==(const Client& other) const; 


    // getter
    const unsigned int getId() const;
    const Name& getName() const;
    const PhoneNumber& getPhoneNumber() const;
    const Point& getPoint() const;

    // setter?

    const string toString() const;
    const static Client createFromString(const std::string& str);

private:
    unsigned int mId;
    Name mName;
    PhoneNumber mPhoneNumber;
    Point mPoint;
};

#endif // CLIENT_H