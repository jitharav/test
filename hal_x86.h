#include <stdio.h>
#include <vector>

using namespace std;

class hvac_hal
{
private:
	vector<float> mocktemp;/*TODO- input mock values chnge to better option*/
	void sleepcp(int milliseconds);

public:
	hvac_hal();
	hvac_hal(vector<float>&  mtemp);
	int readSensor(float* temp);
	int setHeatingOn(const bool heat_on);
	int setCoolingOn(const bool cool_on);
	int setAcOn(const bool hw_on);
	size_t getSize();
};
