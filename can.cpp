#include "can.h"

class CanData : public QSharedData
{
public:

};

Can::Can() : data(new CanData)
{

}

Can::Can(const Can &rhs)
    : data{rhs.data}
{

}

Can &Can::operator=(const Can &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Can::~Can()
{

}
