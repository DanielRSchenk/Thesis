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
    int total_calls = 1000;
    vector<int> delays = create_delay_array(10000, total_calls);

    vector<future<int>> futures;

    // Queue tasks to run on the same thread using std::launch::deferred
    for(int i = 0; i < total_calls; i++) {
        // Use std::launch::deferred to defer task execution until get() is called
        futures.push_back(std::async(std::launch::deferred, ep.disk, delays[i], i));
    }

    // Sequentially retrieve results (tasks will run one by one, but asynchronously scheduled)
    for(int i = 0; i < total_calls; i++) {
        std::cout << "Result: " << futures[i].get() << std::endl;
    }

    return 0;
}

