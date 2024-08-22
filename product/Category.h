#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <regex>
#include <stdexcept>

using namespace std;

class Category {
public:
    Category(const string& category) {
     
        // validation 
        // 어떤걸 해야할지 모르겠어서, 비워둠

        mCategory = category;
    }

    const string& get() const {
        return mCategory;
    }

private:
    string mCategory;
};

#endif // CATEGORY_H
