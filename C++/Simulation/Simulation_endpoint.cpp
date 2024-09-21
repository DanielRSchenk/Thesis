#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include <thread>


using namespace std;

class Endpoint 
{



    public: static int disk(int total_millis, int total_calls) {
        cout << "disk start" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
        return 1;
    }

};

