#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;

class Client
{
public:
    Client(unsigned int id, string name, string phoneNumber, int point = 0);
    ~Client();
    Client(const Client& other);
    bool operator==(const Client& other) const; 


    // getter
    const unsigned int getId() const;
    const string getName() const;
    const string getPhoneNumber() const;
    const int getPoint() const;

    // setter?

    const string toString() const;
    const static Client createFromString(const std::string& str);

private:
    unsigned int mId;
    string mName;
    string mPhoneNumber;
    int mPoint;
};

#endif // CLIENT_H