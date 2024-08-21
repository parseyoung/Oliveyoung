#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "Purchase.h"

using namespace std;

// Purchase Ŭ������ ������ : ��ǰ ID�� Ŭ���̾�Ʈ ID�� �޾� Purchase ��ü�� ����
Purchase::Purchase(unsigned int productId, unsigned int clientId)
    : mProductId(productId)
    , mClientId(clientId)
    , mDate(chrono::system_clock::now())  // ���� �ð��� ���� ��¥�� ����
{
}
// Purchase Ŭ������ ������: ��ǰ ID, Ŭ���̾�Ʈ ID, Ư�� �ð��� �޾� Purchase ��ü�� ����
Purchase::Purchase(unsigned int productId, unsigned int clientId, const chrono::system_clock::time_point& date)
    : mProductId(productId)
    , mClientId(clientId)
    , mDate(date) 
{
}
// ��ǰ ID�� ��ȯ�ϴ� getter �޼ҵ�
const unsigned int Purchase::getProductId() const
{
    return mProductId;
}
// Ŭ���̾�Ʈ ID�� ��ȯ�ϴ� getter �޼ҵ�
const unsigned int Purchase::getClientId() const
{
    return mClientId;
}

// ���� ��¥�� ��ȯ�ϴ� getter �޼ҵ�
const chrono::system_clock::time_point Purchase::getDate() const
{
    return mDate;
}

// �ð��� ���ڿ��� ��ȯ�ϴ� �Լ�
string Purchase::timePointToString(const chrono::system_clock::time_point& timePoint)
{
    std::time_t t = chrono::system_clock::to_time_t(timePoint);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S"); // "YYYY-MM-DD HH:MM:SS" �������� ����
    return oss.str();
}

// ���ڿ��� �ð����� ��ȯ�ϴ� �Լ�
chrono::system_clock::time_point Purchase::stringToTimePoint(const string& dateStr) 
{
    std::tm tm = {};
    std::istringstream iss(dateStr);
    iss >> get_time(&tm, "%Y-%m-%d %H:%M:%S"); // ���ڿ��� �Ľ��Ͽ� std::tm ����ü�� ��ȯ
    if (iss.fail()) {
        throw std::invalid_argument("Invalid date format");
    }
    std::time_t t = std::mktime(&tm);
    return chrono::system_clock::from_time_t(t); // std::tm�� �ð����� ��ȯ
}

// Purchase ��ü�� ���ڿ��� ��ȯ�Ͽ� ��ȯ�ϴ� �Լ�
const string Purchase::toString() const 
{
    return to_string(mProductId) + "," + to_string(mClientId) + "," + timePointToString(mDate);
}

// �־��� ���ڿ��� �̿��Ͽ� Purchase ��ü�� �����ϴ� �Լ�
const Purchase Purchase::createPurchaseFromString(const string& str)
{
    istringstream iss(str);
    char comma;
    unsigned int productId;
    unsigned int clientId;
    string date;

    // ��ǰ ID�� �Ľ�
    if (!(iss >> productId >> comma) || comma != ',') {
        throw invalid_argument("Invalid format for productId");
    }

    // Ŭ���̾�Ʈ ID�� �Ľ�
    if (!(iss >> clientId >> comma) || comma != ',') {
        throw invalid_argument("Invalid format for clientId");
    }

    // ��¥�� �Ľ�
    if (!getline(iss, date)) {
        throw invalid_argument("Invalid format for date");
    }

    return Purchase(productId, clientId, stringToTimePoint(date));
}
