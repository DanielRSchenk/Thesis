#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include "Simulation_endpoint.cpp"


using namespace std;

    int* create_delay_array(int total_millis, int total_calls) {
        int delays[total_calls];
        if (total_millis < total_calls) {
            cout << "Error: millis is lower than calls" << endl;
            return delays;
        }
        cout << "network start" << endl;
    

        //Make delay array where every delay is at least 1 millis
        for  (int i = 0; i < sizeof(delays)/sizeof(int); i++) {
            delays[i] = 1;
        }
        int total_millis_left = total_millis - total_calls;
        while (total_millis_left > 0) {
            delays[rand()%sizeof(delays)/sizeof(int)]++;
            total_millis_left--;
        }
        return delays;
    }

int main(int argc, char* argv[])  
{  
    Endpoint ep;
    int *delays = create_delay_array(10000, 1000);
    cout << &delays[5] << endl;
    
    // std::future<int> test = std::async(std::launch::async, ep.network, 10000, 1000);
    // std::future<int> test2 = std::async(std::launch::async, ep.disk);
    // std::cout << "Result: " << test.get() << std::endl;
    // std::cout << "Result2: " << test2.get() << std::endl;

}

