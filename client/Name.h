#ifndef NAME_H
#define NAME_H

#include <string>
#include <regex>
#include <stdexcept>

using namespace std;

class Name {
public:
    Name(const string& name) {
        if (name.empty()) {
            throw invalid_argument("Name cannot be empty.");
            //throw invalid_argument("이름은 비어 있을 수 없습니다.");
        }

        regex nameRegex("^[가-힣a-zA-Z]+$");
        if (regex_match(name, nameRegex) == false) {
            throw invalid_argument("Name can only contain Korean and English characters.");
            //throw invalid_argument("이름에는 한글과 영어만 포함될 수 있습니다.");
        }

        mName = name;
    }

    const string& get() const {
        return mName;
    }

private:
    string mName;
};

#endif // NAME_H
