/*HVAC Interface Test File*/
#ifndef HVAC_INTERFACE_H
#define HVAC_INTERFACE_H

//#include "pch.h"

#include "gtest\gtest.h"
#include "hvac.h"

class HvacInterfaceTest :public ::testing::Test 
{
protected:
	HvacInterfaceTest();
	virtual  ~HvacInterfaceTest() ;
	virtual void SetUp() ;
	virtual void TearDown() ;
};

#endif//HVAC_INTERFACE_H