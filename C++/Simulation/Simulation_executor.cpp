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


    //This code is written by chatgpt, but is only used for understanding, not for actual testing
    vector<future<int>> futures;
    vector<thread> threads; // Store threads to manage lifecycle
    // Launch tasks asynchronously (but all will complete sequentially on one thread)
    for (int i = 0; i < total_calls; i++) {
        // Use a promise to communicate with the future in a non-blocking way
        promise<int> prom;
        futures.push_back(prom.get_future()); // Get future associated with the promise

        // Launch task in a thread and move promise to ensure the result is set later
        threads.emplace_back([=, p = move(prom)]() mutable {
            int result = ep.disk(delays[i]*1000, i); // Simulate task
            p.set_value(result); // Set the result when done
        });
    }


    // Simulated event loop to check and collect task results asynchronously
    bool tasks_remaining = true;
    while (tasks_remaining) {
        tasks_remaining = false;
        for (int i = 0; i < total_calls; i++) {
            auto status = futures[i].wait_for(chrono::milliseconds(100));
            if (status == future_status::ready) {
                // Retrieve the result and print it
                if (futures[i].valid()) {
                    cout << "Task " << i << " completed with result: " << futures[i].get() << endl;
                }
            } else {
                tasks_remaining = true; // Some tasks are still running
            }
        }

        // Simulate doing other work while waiting for tasks
        cout << "Waiting for tasks to complete..." << endl;
        std::this_thread::sleep_for(chrono::milliseconds(100)); // Pause to simulate non-blocking work
    }

    // Join all threads to ensure they have finished properly
    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
    return 0;
}

