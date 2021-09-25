//
//  main.cpp
//  SctCppTimer
//
//  Created by Steffen A. Mork on 24.09.21.
//

#include <iostream>
#include <unistd.h>

#include "CppTimer.h"

using namespace sc::timer;
using namespace std::chrono;

int main(int argc, const char * argv[])
{
    CppTimer a;
    CppTimer b;
    CppTimer c;
    
    std::cout << "--------------------------" << std::endl << std::flush;
    a.start(2s);
    b.start(700ms, false);
    sleep(3);

    std::cout << "--------------------------" << std::endl << std::flush;
    a.stop();
    a.start(2500ms, false);
    sleep (7);

    std::cout << "--------------------------" << std::endl << std::flush;
    a.stop();
    b.stop();
    return 0;
}
