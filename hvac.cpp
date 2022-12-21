// hvac.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include "pch.h"
#include "hvac.h"

#define HVAC_THRESHOLD 3//+,_ 3 degrees

//CPP File

int  HvacCtrl::readTempsensor(float* currtemp)
{

    int nRet = mhvac_hw.readSensor(currtemp);
    return nRet;
}
int  HvacCtrl::monitorControl(int *mintrigger,int* maxtrigger)
{
    int  senret = 0;
    int min = 0;
    int max = 0;
    bMonitoring = 1;
    //Init hardware;
    while (true == bMonitoring)
    {
        float currtemp = 0.0f;
        senret = readTempsensor(&currtemp);
        cout << senret;

        cout << "***Current temperature is" << currtemp;

        if (0 == senret)
        {
            mtx.lock();
            if (currtemp < (mintemp + 3.0f))//within threshold
            {
                ac_heating_on();
                    min++;
                    cout << " cutoff thermistor";
            }
            else if (currtemp > (maxtemp-3.0f))
            {
                ac_cooling_on();
                    max++;
                    //cooling on
                    cout << " cooling on \n" << endl;
            }
            else
            {
                cout << " heating/cooling off \n" << endl;
                ac_heating_off();
                ac_cooling_off();
            }//if
            mtx.unlock();
        }
        else
        {
            cout << "End of dummy data"; cout << endl;
            senret = HVAC_ESENSOR_FAIL;
            break;
        }//if
    }//while
    cout << "min is"; cout << min; cout << endl;
    cout << "max is"; cout << max; cout << endl;
   *mintrigger = min;
   *maxtrigger = max;
   return senret;
}
int HvacCtrl::changeTemp(float mintemp, float maxtemp)
{
    if( (mintemp >= -150)&& (maxtemp<=150))//farenheit
    {
        mtx.lock();
        this->maxtemp = maxtemp;
        this->mintemp = mintemp;
        mtx.unlock();
        cout << "Min and Max temp";
        cout << endl;
        cout << maxtemp;
        cout << mintemp;
        cout << endl;
        return HVAC_EOK;
    }
    else
    {
        return HVAC_EINVALID_PARAM;
    }
}
    
int HvacCtrl::ac_on()
{
    int nRet = HVAC_EFAIL;
    if (HVAC_STATE_CHANGE == current->ac_on(this))
    {
        nRet=mhvac_hw.setAcOn(true);
        Notify(mintemp, maxtemp);//state change notify
    }
    return nRet;
 
}

int HvacCtrl::ac_cooling_on()
{
    int nRet = HVAC_EFAIL;
    if (HVAC_STATE_CHANGE == current->ac_cooling_on(this))
    {
        nRet = mhvac_hw.setCoolingOn(true);
        Notify(mintemp, maxtemp);//state change notify
    }
    return nRet;
}
int HvacCtrl::ac_heating_on()
{
    int nRet = HVAC_EFAIL;
    if (HVAC_STATE_CHANGE == current->ac_heating_on(this))
    {
        nRet = mhvac_hw.setHeatingOn(true);
        Notify(mintemp, maxtemp);//state change notify
    }
    return nRet;
}
int HvacCtrl::ac_cooling_off()
{
    int nRet = HVAC_EFAIL;
    if (HVAC_STATE_CHANGE == current->ac_cooling_off(this))
    {
        nRet = mhvac_hw.setCoolingOn(false);
        Notify(mintemp, maxtemp);//state change notify
    }
    return nRet;
}
int HvacCtrl::ac_heating_off()
{
    int nRet = HVAC_EFAIL;
    if (HVAC_STATE_CHANGE == current->ac_heating_off(this))
    {
        nRet = mhvac_hw.setHeatingOn(false);
       Notify(mintemp, maxtemp);//state change notify
    }
    return nRet;
}
int HvacCtrl::ac_off()
{
    int nRet = HVAC_EFAIL;
    if (HVAC_STATE_CHANGE == current->ac_off(this))
    {
        nRet = mhvac_hw.setAcOn(false);
        Notify(mintemp, maxtemp);//state change notify
    }
    cout << "AC OFF";
    cout << endl;
    return nRet;
}



class hvac_on : public State
{
public:
    hvac_on()
    {
        cout << "   ON-ctor ";
    };
    ~hvac_on()
    {
        cout << "   dtor-ON\n";
    };
    
    int ac_off(HvacCtrl* m);
    int cooling_on(HvacCtrl* m);
    int heating_on(HvacCtrl* m);
 };

class hvac_off : public State
{
public:
    hvac_off()
    {
        cout << " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%OFF-ctor ";
    };
    ~hvac_off()
    {
        cout << "   dtor-OFF\n";
    };
   
    int ac_on(HvacCtrl* m)
    {
        cout << "   going from OFF to ON";
        m->setCurrent(new hvac_on());
        delete this;
        return HVAC_STATE_CHANGE;
    }

};
int hvac_on::ac_off(HvacCtrl* m)
{
    cout << "   going from ON to OFF";
    m->setCurrent(new hvac_off());
    delete this;
    return HVAC_STATE_CHANGE;
}

class hvac_cooling_on : public State
{
public:
    hvac_cooling_on()
    {
        cout << "   Coling_on -ctor ";
    };
    ~hvac_cooling_on()
    {
        cout << "   dtor-cooling_on\n";
    };

    int cooling_off(HvacCtrl* m)
    {
        m->setCurrent(new hvac_on());
       delete this;
       return HVAC_STATE_CHANGE;
     }

};
int  hvac_on::cooling_on(HvacCtrl* m)
{
   m->setCurrent(new hvac_cooling_on());
   delete this;
   return HVAC_STATE_CHANGE;
   
}
class hvac_heating_on : public State
{
public:
    hvac_heating_on()
    {
        cout << "   Heating_on -ctor ";
    };
    ~hvac_heating_on()
    {
        cout << "   dtor-heating_on\n";
    };

    int heatiing_off(HvacCtrl* m)
    {
        m->setCurrent(new hvac_on());
        delete this;
        return HVAC_STATE_CHANGE;
    }

};

/*

int main()
{
   HvacCtrl daikin_ac;

    // Two clients
    client daikin_client1;
    client daikin_client2;

    daikin_ac.Attach(&daikin_client1);
    daikin_ac.Attach(&daikin_client2);
    hvac_hal hw_hal;
    daikin_ac.init(hw_hal);
    //Set AC min and max value
    daikin_ac.ChangeTemp(330.0f,450.0f);
    int mintrigger = 0;
    int maxtrigger = 0;
    daikin_ac.monitorControl(&mintrigger,&maxtrigger);

    //client unsuscribe
   // daikin_ac.Detach(&daikin_client2);
    while (1);

    //NSet another temperature
    //daikin_ac.ChangeTemp(26.0f,46.0f);

    return 0;
}*/

size_t  HvacCtrl::init(hvac_hal hvac_hal)
{
    //Init hardware;
    mhvac_hw = hvac_hal;
    size_t nRet = hvac_hal.getSize();
    current = new hvac_off();
    return nRet;

}
void   HvacCtrl::cleanup()
{
    delete current;

}