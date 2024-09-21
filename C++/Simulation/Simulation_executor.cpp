#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include "Simulation_endpoint.cpp"
#include <vector>


using namespace std;

    vector<int> create_delay_array(int total_millis, int total_calls) {
        vector<int> delays(total_calls, 1);
        if (total_millis < total_calls) {
            cout << "Error: millis is lower than calls" << endl;
            return delays;
        }
        cout << "network start" << endl;

        srand(time(0));
        int total_millis_left = total_millis - total_calls;
        while (total_millis_left > 0) {
            delays[rand() % total_calls]++;
            total_millis_left--;
        }
        for(int i = 0; i < total_calls; i++) {
            cout << delays[i] << " ";
        }
        return delays;
    }

int main(int argc, char* argv[])  
{  
    Endpoint ep;
    vector<int> delays = create_delay_array(10000, 1000);
    cout << delays[1] << endl;
    
    // std::future<int> test = std::async(std::launch::async, ep.network, 10000, 1000);
    // std::future<int> test2 = std::async(std::launch::async, ep.disk);
    // std::cout << "Result: " << test.get() << std::endl;
    // std::cout << "Result2: " << test2.get() << std::endl;
    return 0;
}

