#include "gtest/gtest.h"
#include "hvac_interface.h"

int main(int argc, char** argv) {
    char* option[] = { "test.exe", //it doesn't have meaning, just dummy
                       "--gtest_output=xml:Hvac_gtest.xml" };
    int argc1 = 2;
    ::testing::InitGoogleTest(&argc1, option);
    return RUN_ALL_TESTS();
}
HvacInterfaceTest::HvacInterfaceTest()
{

}
HvacInterfaceTest::~HvacInterfaceTest()
{

}
void HvacInterfaceTest::SetUp()
{
   
}
void HvacInterfaceTest::TearDown()
{
    

}

TEST(HvacInterfaceTest, TCx0100Monitor_Init_mock1) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
 
    vector<float>  test{ 0.0f };
    hvac_hal hw_hal(test);
    size_t n=daikin_ac.init(hw_hal);

    EXPECT_EQ(1, n);
   
}
TEST(HvacInterfaceTest, TCx0101Monitor_Init_mock2) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);

    EXPECT_EQ(3, n);

}
TEST(HvacInterfaceTest, TCx0101Monitor_Init_cleanup_mock2) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    daikin_ac.cleanup();
    EXPECT_EQ(3, n);

}
TEST(HvacInterfaceTest, TCx0102Monitor_Init_ac_on) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    
     n = daikin_ac.ac_on();
     daikin_ac.cleanup();

    EXPECT_EQ(HVAC_EOK, n);

}
TEST(HvacInterfaceTest, TCx0103Monitor_Init_ac_on_off) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
   
    n = daikin_ac.ac_on();
    EXPECT_EQ(HVAC_EOK, n);
    n= daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(HVAC_EOK, n);

}
TEST(HvacInterfaceTest, TCx0103Monitor_Init_ac_on_off_loop) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    for (int count = 0; count < 100; count++)
    {

        n = daikin_ac.ac_on();
        EXPECT_EQ(HVAC_EOK, n);
        n = daikin_ac.ac_off();
        EXPECT_EQ(HVAC_EOK, n);
    }
    daikin_ac.cleanup();
    EXPECT_EQ(HVAC_EOK, n);

}
TEST(HvacInterfaceTest, TCx0103Monitor_Init_ac_on_loop) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    for (int count = 0; count < 100; count++)
    {

        n = daikin_ac.ac_on();
             
    }
    EXPECT_EQ(HVAC_EFAIL, n);
    daikin_ac.cleanup();
    
}
TEST(HvacInterfaceTest, TCx0103Monitor_Init_ac_off_loop) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    for (int count = 0; count < 100; count++)
    {

        n = daikin_ac.ac_off();
        
    }
    EXPECT_EQ(HVAC_EFAIL, n);
    daikin_ac.cleanup();
    
}
TEST(HvacInterfaceTest, TCx0103Monitor_Init_ac_init_on_off_cleanup_loop) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    for (int count = 0; count < 100; count++)
    {
        size_t n = daikin_ac.init(hw_hal);

        n = daikin_ac.ac_on();
        EXPECT_EQ(HVAC_EOK, n);
        n = daikin_ac.ac_off();
        EXPECT_EQ(HVAC_EOK, n);

        daikin_ac.cleanup();
        EXPECT_EQ(HVAC_EOK, n);
    }

}
TEST(HvacInterfaceTest, TCx0103Monitor_change_temp) {
    //Set AC min and max value
    HvacCtrl daikin_ac;

    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(50.0, 80.0);
    daikin_ac.cleanup();
    EXPECT_EQ(HVAC_EOK, n);

}
TEST(HvacInterfaceTest, TCx0103Monitor_change_temp_out_of_bounds) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(-150.0, 200.0);
    daikin_ac.cleanup();
    EXPECT_EQ(HVAC_EINVALID_PARAM, n);

}
TEST(HvacInterfaceTest, TCx0103Monitor_change_max_limit) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(FLT_MIN,FLT_MAX);
    daikin_ac.cleanup();
    EXPECT_EQ(HVAC_EINVALID_PARAM, n);

}
TEST(HvacInterfaceTest, TCx0103Monitor_monitor_temp_normal) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test{ 0.0f,1.0f,2.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(20.0f, 30.0f);
    int min = 0; int max = 0;
    n = daikin_ac.ac_on();
    n= daikin_ac.monitorControl(min, max);
    n = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, n);
    EXPECT_EQ(3, min);
    EXPECT_EQ(0, max);
}

TEST(HvacInterfaceTest, TCx0103Monitor_monitor_temp_normal_cooling_on) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test{ 80.0f,100.0f};
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(20.0f,30.0f);
    int min = 0; int max = 0;
    n = daikin_ac.ac_on();
    n = daikin_ac.monitorControl(min, max);
    n = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, min);
    EXPECT_EQ(2, max);
}
TEST(HvacInterfaceTest, TCx0103Monitor_monitor_temp_heating_cooling_off) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test{ 21.0f,22.0f,23.0f,24.0f,25.0f,26.0f,27.0f,28.0f,29.0f,29.5f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(17.0f, 35.0f);
    int min = 0; int max = 0;
    n = daikin_ac.ac_on();
    n = daikin_ac.monitorControl(min, max);
    n = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, n);
    EXPECT_EQ(0, min);
    EXPECT_EQ(0, max);
}
TEST(HvacInterfaceTest, TCx0103Monitor_monitor_temp_alternate_heating_cooling) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test{ 18.0f,39.0f,17.0f,40.0f,16.0f,41.0f,15.1f,42.9f,17.9f,42.8f };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(17.0f, 35.0f);
    int min = 0; int max = 0;
    n = daikin_ac.ac_on();
    n = daikin_ac.monitorControl(min, max);
    n = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, n);
    EXPECT_EQ(5, min);
    EXPECT_EQ(5, max);
}
TEST(HvacInterfaceTest, TCx0103Monitor_monitor_temp_max_float_limit){
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test{ FLT_MIN,FLT_MAX };
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(17.0f, 35.0f);
    int min = 0; int max = 0;
    n = daikin_ac.ac_on();
    n = daikin_ac.monitorControl(min, max);
    n = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, n);
    EXPECT_EQ(1, min);
    EXPECT_EQ(1, max);
}

TEST(HvacInterfaceTest, TCx0103Monitor_monitor_temp_huge_data) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test;
    for (int i = 0; i <= 100; i++)
    {
        test.push_back((float)rand());
    }
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(17.0f, 35.0f);
    int min = 0; int max = 0;
    n = daikin_ac.ac_on();
    n = daikin_ac.monitorControl(min, max);
    n = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, n);
   
}
TEST(HvacInterfaceTest, TCx0103Monitor_monitor_temp_huge_data_default_min_max_temp) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test;
    for (int i = 0; i <= 100; i++)
    {
        test.push_back((float)rand());
    }
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    int min = 0; int max = 0;
    n = daikin_ac.ac_on();
    n = daikin_ac.monitorControl(min, max);
    n = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, n);

}
TEST(HvacInterfaceTest, TCx0100Monitor_AC_ON_OFF_monitor) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test;
    for (int i = 0; i <= 10000; i++)
    {
        test.push_back((float)rand());
    }
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    int  nret = daikin_ac.ac_on();
   
    n = daikin_ac.changeTemp(17.0f, 35.0f);
    int min = 0; int max = 0;
    n = daikin_ac.monitorControl(min, max);
    nret = daikin_ac.ac_off();
    daikin_ac.cleanup();
    EXPECT_EQ(0, nret);

}
#if 0
TEST(HvacInterfaceTest, TCx0100Monitor_huge_loop) {
    //Set AC min and max value
    HvacCtrl daikin_ac;
    vector<float>  test;
    for (int i = 0; i <= 10000000; i++)
    {
        test.push_back((float)rand());
    }
    hvac_hal hw_hal(test);
    size_t n = daikin_ac.init(hw_hal);
    n = daikin_ac.changeTemp(17.0f, 35.0f);
    int min = 0; int max = 0;
    n = daikin_ac.monitorControl(min, max);
    daikin_ac.cleanup();
    EXPECT_EQ(HVAC_ESENSOR_FAIL, n);

}

#endif
