#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include <thread>


using namespace std;

class Endpoint 
{



    public: static int database(int millis, int nr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(millis));
        return nr;
    }

};

