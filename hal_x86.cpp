
//#include "pch.h"
#include "hal_x86.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif // _WIN32
hvac_hal::hvac_hal()
{
	
}
size_t hvac_hal::getSize()
{
	size_t nRet = mocktemp.size();
	return nRet;
}

hvac_hal::hvac_hal(vector<float>& mtemp)
{
	mocktemp = mtemp;
	cout << "The vector elements are: ";
	for (int i = 0; i < mocktemp.size(); i++)
		cout << mocktemp[i] << " ";
}
void  hvac_hal :: sleepcp(int milliseconds) // Cross-platform sleep function
{
#ifdef _WIN32

	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif // _WIN32
}

int hvac_hal::readSensor(float *temp)

{
	
	//std::vector<float> fakeval{ -FLT_MAX ,-300.0f,-200.1f, -180.9f,-45.7f,-30.1f,-7.0f,-4.5f,-0.1f,0.0f,0.02f,44.5f,63.2f,400.0f,FLT_MAX };
	//static auto it = mocktemp.begin();
	cout << "&&&&&&&&&&&&Readsesnsor&&&&&&&&&&&&"; cout << endl;
	for (auto i = mocktemp.begin(); i != mocktemp.end(); ++i)
	{
		*temp = *i;
		mocktemp.erase(i);
		return 0;
	}
	return 1;
}
int hvac_hal::setCoolingOn(const bool cool)
{
	sleepcp(100);
	return 0;
}
int hvac_hal::setHeatingOn(const bool heat)
{
	sleepcp(100);
	return 0;
}
int hvac_hal::setAcOn(const bool ac_on)
{
	sleepcp(100);
	return 0;
}