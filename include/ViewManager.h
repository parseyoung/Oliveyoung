#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

class ViewManager
{
public:
    virtual ~ViewManager() = default;

    virtual const bool displayMenu() = 0;
    virtual void displayItemsInfo() const = 0;
    virtual void inputItem() = 0;
};

#endif // VIEW_MANAGER_H
