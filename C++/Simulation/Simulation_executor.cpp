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

        srand(time(0));
        int total_millis_left = total_millis - total_calls;
        while (total_millis_left > 0) {
            delays[rand() % total_calls]++;
            total_millis_left--;
        }
        for(int i = 0; i < total_calls; i++) {
            //cout << delays[i] << " ";
        }
        return delays;
    }


    int main(int argc, char* argv[])  
    {  

        int total_calls = 1000;
        int total_delays = 10000;
        vector<int> delays = create_delay_array(total_delays, total_calls);

        Endpoint ep;

        //Async version
        auto start_async = chrono::high_resolution_clock::now();
    
        ios_base::sync_with_stdio(false);
    
        std::vector<std::future<std::int32_t>> tasks;
        for (int i = 0; i <  delays.size(); i++) {
            //cout << i << endl;
            tasks.push_back(std::async(std::launch::async, ep.database, delays[i], i));
        }
        for (auto &task : tasks) {
            std::int32_t result = task.get();
        }
    
        auto end_async = chrono::high_resolution_clock::now();
        double time_taken_async = chrono::duration_cast<chrono::nanoseconds>(end_async - start_async).count();
        time_taken_async *= 1e-9;
    
        cout << "Time taken by async rogram is : " << time_taken_async << "seconds" << endl;

        //Sync version
        auto start_sync = chrono::high_resolution_clock::now();
    
        ios_base::sync_with_stdio(false);
    
        for (int i = 0; i <  delays.size(); i++) {
            //cout << i << endl;
            ep.database(delays[i], i);
        }
    
        auto end_sync = chrono::high_resolution_clock::now();
        double time_taken_sync = chrono::duration_cast<chrono::nanoseconds>(end_sync - start_sync).count();
        time_taken_sync *= 1e-9;
    
        cout << "Time taken by sync rogram is : " << time_taken_sync << "seconds" << endl;

        return 0;
    }

