#ifndef POINT_H
#define POINT_H

#include <stdexcept>

class Point {
public:
    Point(int point) {
        if (point < 0) {
            throw invalid_argument("포인트는 음수가 될 수 없습니다.");
        }
        mPoint = point;
    }

    int get() const {
        return mPoint;
    }

    void addPoints(int points) {
        if (points < 0) {
            throw invalid_argument("포인트를 음수로 추가할 수 없습니다.");
        }
        
        mPoint += points;
    }

private:
    int mPoint;
};

#endif // POINT_H
