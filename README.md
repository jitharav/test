# test project-Study project to monitor an ac.

Implemented using various states and observer design concepts.
Major files/functions description are as below


hvac.h/hvac.cpp-interface class that contains the public functions to monitor an ac.
  init-initialises the hardware.
  
  changeTemp-Set min and max temperature limits.
  
  monitorControl-Monitors and ensures that the ac is in the prescribed temperature limits.
  
  ac_on-power on the hardware
  
  ac_off-power off the hardware
  
 cleanup-Resource freeing(memory,handles etc)
 
hvac_observer.h/hvac_observer.cpp-Implementation of observer so that clients can register for notifications(eg:remote,control panel UI etc).

hvac_x86.h/hvac_x86.cpp Dummy HAL functions in x86.

test.cpp/hvac_interface.h-Google test case implemenation.


CMakelists-will generate visual studio projects for the file.

The gtest libraries(gtest.leb,gtest_main.lib) should be available in ${CMAKE_SOURCE_DIR}/lib") folder.


Hvac_gtest.xml-Test report generated in xml for CI/CD.

