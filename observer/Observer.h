#ifndef __OBSERVER_H_
#define __OBSERVER_H_

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(unsigned int id) = 0;
};
#endif//__OBSERVER_H_