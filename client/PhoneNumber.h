#ifndef PHONENUMBER_H
#define PHONENUMBER_H

#include <string>
#include <regex>
#include <stdexcept>

using namespace std;

class PhoneNumber {
public:
    PhoneNumber(const string& phoneNumber) {
        regex phoneRegex("^010(\\d{3,4})(\\d{4})$");
        smatch match;

        if (!regex_match(phoneNumber, match, phoneRegex)) {
            throw invalid_argument("유효하지 않은 전화번호입니다. 010으로 시작하는 11자리 번호만 허용됩니다.");
        }

        mPhoneNumber = phoneNumber;
        mMiddleNumber = match[1];
        mEndNumber = match[2];
    }

    const string& getFullNumber() const {
        return mPhoneNumber;
    }

    const string& getMiddleNumber() const {
        return mMiddleNumber;
    }

    const string& getEndNumber() const {
        return mEndNumber;
    }

private:
    string mPhoneNumber;
    
    string mMiddleNumber;
    string mEndNumber;
};

#endif // PHONENUMBER_H
