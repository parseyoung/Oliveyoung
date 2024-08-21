#include "Validation.h"
#include <iostream>
#include <regex>

// Product 관련 검증 메소드
bool Validation::validateProductName(const std::string& name) {
    if (name.empty()) {
        std::cout << "Error: Product name cannot be empty." << std::endl;
        return false;
    }
    if (name.length() > 50) {  // 제품 이름 길이 제한
        std::cout << "Error: Product name is too long. Please enter a name with 50 characters or less." << std::endl;
        return false;
    }
    return true;
}

bool Validation::validateProductPrice(int price) {
    if (price < 0) {
        std::cout << "Error: Price must be a non-negative integer." << std::endl;
        return false;
    }
    return true;
}

bool Validation::validateProductCategory(const std::string& category) {
    if (category.empty()) {
        std::cout << "Error: Category cannot be empty." << std::endl;
        return false;
    }
    if (category.length() > 30) {  // 카테고리 길이 제한
        std::cout << "Error: Category is too long. Please enter a category with 30 characters or less." << std::endl;
        return false;
    }
    return true;
}

// Client 관련 검증 메소드
bool Validation::validateClientName(const std::string& name) {
    if (name.empty()) {
        std::cout << "Error: Client name cannot be empty." << std::endl;
        return false;
    }
    if (name.length() > 20) {  // 클라이언트 이름 길이 제한
        std::cout << "Error: Client name is too long. Please enter a name with 20 characters or less." << std::endl;
        return false;
    }
    return true;
}

bool Validation::validateClientPhoneNumber(const std::string& phoneNumber) {
    std::regex pattern1("^010-\\d{4}-\\d{4}$");
    std::regex pattern2("^010\\d{8}$");
    if (!std::regex_match(phoneNumber, pattern1) && !std::regex_match(phoneNumber, pattern2)) {
        std::cout << "Error: Phone number must be in the format 010-0000-0000 or 01000000000." << std::endl;
        return false;
    }
    return true;
}

bool Validation::validateClientPoints(int points) {
    if (points < 0) {
        std::cout << "Error: Points must be a non-negative integer." << std::endl;
        return false;
    }
    return true;
}
