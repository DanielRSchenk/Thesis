#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <future>  // For std::async
#include <vector>  // For managing multiple futures
#include <string>  // For stoll
#include <mutex>   // For std::mutex
#include <atomic>  // For std::atomic

using namespace std;

mutex mtx;

// Progress tracker
atomic<long long int> progress(0);

double pi_partial(long long int start, long long int end, long long int total_steps, long long int step_size) {
    double pi_4 = 0;
    int sign = (start % 4 == 1) ? 1 : -1; 

    for (long long int i = start; i < end; i += 2) {
        pi_4 += sign * (1.0 / i);
        sign *= -1; 

        // Update progress every 'step_size' iterations
        progress += 2;
        if (progress % step_size == 0) {
            lock_guard<mutex> lock(mtx); 
            int percentage = 100 * (double)progress / (double)total_steps;

            // Percentage was always 175% so divide by 1.75 as a workaround
            cout << '\r' << fixed << setprecision(51) << "Progress: " << percentage << "% " << flush;
            //  if (percentage > 98)
            //     cout << '\r' << fixed << setprecision(51) << "Progress: " << 100 << "% " << flush;
        }
    }

    return pi_4;
}

double pi_async(long long int n, int num_threads) {

    long long int step = n / num_threads;
    vector<future<double>> futures;

    // Launch threads to compute different parts of the pi sum
    long long int step_size = n / 100; 
    for (int i = 0; i < num_threads; ++i) {
         // Adjust the start and end for each thread
        long long int start = 1 + i * step * 2; 
        long long int end = (i == num_threads - 1) ? n : (i + 1) * step * 2;

        futures.push_back(async(launch::async, pi_partial, start, end, n, step_size));
    }

    // Aggregate the results from all threads
    double pi_4 = 0;
    for (auto& fut : futures) {
        pi_4 += fut.get();
    }

    cout << "\nCalculation complete!" << endl;
    return 4.0 * pi_4; 
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << " <n>" << " <threads> " << endl;
        return 1; 
    }

    // Declare variables
    long long int n = stoll(argv[1]);
    int threads = atoi(argv[2]);
    int num_threads = threads;

    // Print response with high precision
    cout << pi_async(n, num_threads) << endl;

    return 0;
}
