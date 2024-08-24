#ifndef __SUBJECT_H_
#define __SUBJECT_H_
#include "../observer/Observer.h"
class Subject
{
public:
    Subject() = default;
    virtual ~Subject() = default;
    virtual void subscribe(Observer *o) = 0;
    virtual void unsubscribe(Observer *o) = 0;
    virtual void notify(unsigned int id)=0;
};

#endif//__SUBJECT_H_