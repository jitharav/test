//hvac_observer.cpp-implementation of observer classes to get notification of state changes of ac
#include "hvac.h"
#include "hvac_observer.h"
#include <iostream>

void client::Update(float mintemp, float maxtemp)
{
    this->mintemp = mintemp;
    this->maxtemp = maxtemp;
    this->st = st;

    //Lets print on console just to test the working
    std::cout << "Min Temp at " << mintemp << " state is now " << st << " Max Temp at " << maxtemp << "\n";
}
void Hvac::Attach(client* remote)
{
    list.push_back(remote);
}
void Hvac::Detach(client* remote)
{
    list.erase(std::remove(list.begin(), list.end(), remote), list.end());
}

void Hvac::Notify(float mintemp, float maxtemp)
{
    for (vector<client*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        if (*iter != 0)
        {
            (*iter)->Update(mintemp, maxtemp);
        }
    }
}

