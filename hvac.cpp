// hvac.cpp : This file contains the interface functions implementation and various state classes.
//#include "pch.h"
#include "hvac.h"

#define HVAC_THRESHOLD 3//+,_ 3 degrees

//CPP File

int  HvacCtrl::readTempsensor(float& currtemp)
{

    int nRet = mhvac_hw.readSensor(currtemp);
    return nRet;
}
int  HvacCtrl::monitorControl(int& mintrigger,int& maxtrigger)
{
    int  senret = 0;
    int min = 0;
    int max = 0;
    bMonitoring = 1;
    //Init hardware;
    while (true == bMonitoring)
    {
        float currtemp = 0.0f;
        senret = readTempsensor(currtemp);
       

        if (0 == senret)
        {
            mtx.lock();
            if (currtemp < (mintemp + 3.0f))//within threshold
            {
                ac_heating_on();
                min++;
                
            }
            else if (currtemp > (maxtemp-3.0f))
            {
                ac_cooling_on();
                max++;
                //cooling on
               
            }
            else
            {
                
                ac_heating_off();
                ac_cooling_off();
            }//if
            mtx.unlock();
        }
        else
        {
           
            senret = HVAC_ESENSOR_FAIL;
            break;
        }//if
    }//while
 
    mintrigger = min;
    maxtrigger = max;
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
    
    return nRet;
}



class hvac_on : public State
{
public:
    hvac_on()
    {
       
    };
    ~hvac_on()
    {
       
    };
    
    int ac_off(HvacCtrl* m);
    int ac_cooling_on(HvacCtrl* m);
    int ac_heating_on(HvacCtrl* m);

 };

class hvac_off : public State
{
public:
    hvac_off()
    {
        
    };
    ~hvac_off()
    {
       
    };
   
    int ac_on(HvacCtrl* m)
    {
        
        m->setCurrent(new hvac_on());
        delete this;
        return HVAC_STATE_CHANGE;
    }
    int ac_cooling_on(HvacCtrl* m)
    {
        return HVAC_STATE_CHANGE_ERROR;
    }
    int ac_heating_on(HvacCtrl* m)
    {
        return HVAC_STATE_CHANGE_ERROR;
    }
    int ac_cooling_off(HvacCtrl* m)
    {
        return HVAC_STATE_CHANGE_ERROR;
    }
    int ac_heating_off(HvacCtrl* m)
    {
        return HVAC_STATE_CHANGE_ERROR;
    }


};
int hvac_on::ac_off(HvacCtrl* m)
{
    
    m->setCurrent(new hvac_off());
    delete this;
    return HVAC_STATE_CHANGE;
}

class hvac_cooling_on : public State
{
public:
    hvac_cooling_on()
    {
        
    };
    ~hvac_cooling_on()
    {
        
    };
    int ac_heating_on(HvacCtrl* m);
    int ac_cooling_off(HvacCtrl* m)
    {
        m->setCurrent(new hvac_on());
       delete this;
       return HVAC_STATE_CHANGE;
     }


  
    int ac_heating_off(HvacCtrl* m)
    {
        return HVAC_STATE_CHANGE_ERROR;
    }
    int ac_off(HvacCtrl* m)
    {
        m->setCurrent(new hvac_off());
        delete this;
        return HVAC_STATE_CHANGE;
    }

};
int  hvac_on::ac_cooling_on(HvacCtrl* m)
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
        
    };
    ~hvac_heating_on()
    {
       
    };

    int ac_heatiing_off(HvacCtrl* m)
    {
        m->setCurrent(new hvac_on());
        delete this;
        return HVAC_STATE_CHANGE;
    }

    int ac_cooling_on(HvacCtrl* m)
    {
        m->setCurrent(new hvac_cooling_on());
        delete this;
        return HVAC_STATE_CHANGE;
    }

    int ac_cooling_off()
    {
        return HVAC_STATE_CHANGE_ERROR;
    }
    int ac_off(HvacCtrl* m)
    {
        m->setCurrent(new hvac_off());
        delete this;
        return HVAC_STATE_CHANGE;
    }


};
int hvac_cooling_on::ac_heating_on(HvacCtrl* m)
{
    m->setCurrent(new hvac_heating_on());
    delete this;
    return HVAC_STATE_CHANGE;
}
int  hvac_on::ac_heating_on(HvacCtrl* m)
{
    m->setCurrent(new hvac_heating_on());
    delete this;
    return HVAC_STATE_CHANGE;

}

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