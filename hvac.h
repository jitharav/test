#include <iostream>
#include <vector>
#include <mutex>
#include "hal_x86.h"
#include "hvac_observer.h"


#define HVAC_EOK 0u
#define HVAC_EMOCK_DATA_END 1u
#define HVAC_ESENSOR_FAIL 2u
#define HVAC_STATE_CHANGE 3u
#define HVAC_EFAIL 4u
#define HVAC_EINVALID_PARAM 5u


class Hvac
{
    //List of observers
    std::vector<client*> list;

public:
    void Attach(client* remote);
    void Detach(client* remote);
    void Notify(float mintemp, float maxtemp);
};
//HVAC Interface class
class HvacCtrl : public Hvac
{

private:
    class State* current;//State of hardware
    bool bMonitoring = 0;//is ac monitoring on
    std::mutex mtx;//lock
    float mintemp = 40.0f;//default min temp limit
    float maxtemp =100.0f;//default max temp limit
    class hvac_hal    mhvac_hw;//HW Hal/Driver API -x86 or ARM
    int  readTempsensor(float& currtemp); // temperature from hw sensor

    int ac_cooling_on();
    int ac_heating_off();
    int ac_cooling_off();
    int ac_heating_on();
  
public:
    size_t  init(hvac_hal mhvac_hw);
    void cleanup();
    int  changeTemp(float mintemp, float maxtemp);
    int  monitorControl(int& mintrigger, int& maxtrigger);
    int  ac_on();
    int  ac_off();
    void setCurrent(State* s)
    {
        current = s;
    }
  
};

class State
{

public:

    virtual int ac_on(HvacCtrl* m)
    {
        cout << "Already on";
        return HVAC_EOK;
    }

    virtual int ac_off(HvacCtrl* m)
    {
        cout << "Already off";
        return HVAC_EOK;
    }
    virtual int  ac_cooling_on(HvacCtrl* m)
    {
        cout << "Already cooling on";
        return HVAC_EOK;
    }

    virtual int ac_heating_on(HvacCtrl* m)
    {
        cout << "Already Heating on";
        return HVAC_EOK;
    }
    virtual int  ac_cooling_off(HvacCtrl* m)
    {
        cout << "Already cooling on";
        return HVAC_EOK;
    }

    virtual int ac_heating_off(HvacCtrl* m)
    {
        cout << "Already Heating on";
        return HVAC_EOK;
    }
};
