#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

class Validation {
public:
    // Product 관련 검증 메소드
    static bool validateProductName(const std::string& name);
    static bool validateProductPrice(int price);
    static bool validateProductCategory(const std::string& category);

    // Client 관련 검증 메소드
    static bool validateClientName(const std::string& name);
    static bool validateClientPhoneNumber(const std::string& phoneNumber);
    static bool validateClientPoints(int points);
};

#endif // VALIDATION_H
