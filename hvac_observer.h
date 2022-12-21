#pragma once
using namespace std; enum state
{
    STATE_OFF,
    STATE_WORKING,
    STATE_ERROR,
    STATE_SERVICE
};
class IObserver
{
public:
    virtual void Update(float mintemp, float maxtemp) = 0;
};
class client : IObserver
{
    //Name of the Shop

    float mintemp = 0;
    float maxtemp = 0;
    state st = STATE_OFF;
public:

    void Update(float mintemp, float maxtemp);
};
