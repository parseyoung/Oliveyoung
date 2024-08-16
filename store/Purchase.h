#include <string>
#include <chrono>

using namespace std;

class Purchase 
{
public:
    Purchase(unsigned int productId, unsigned int clientId);
    Purchase(unsigned int productId, unsigned int clientId, const chrono::system_clock::time_point& date);

    const unsigned int getProductId() const;
    const unsigned int getClientId() const;
    const chrono::system_clock::time_point getDate() const;

    const string toString() const;
    static const Purchase createPurchaseFromString(const string& str);
    // Helper method to convert time_point to string
    static string timePointToString(const chrono::system_clock::time_point& timePoint);

private:
   
    // Helper method to convert string to time_point
    static chrono::system_clock::time_point stringToTimePoint(const string& dateStr);

    unsigned int mProductId;
    unsigned int mClientId;
    chrono::system_clock::time_point mDate;
};
