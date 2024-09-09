#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <future>
#include <vector>
#include <string>

using namespace std;

double pi_partial(long long int start, long long int end) {
    double pi_4 = 0;
    int sign = (start % 4 == 1) ? 1 : -1;
    int percent = 0;
    long long int percent_step = (start+end)/100;
    long long int step = 0;


    for (long long int i = start; i < end; i += 2) {
        step++;
        if (start == 1 && percent < 100 && step % percent_step == 1) {
            percent+=2;
            cout << '\r' << percent << "% " << flush;
            if (percent >= 99)
                cout << "\nCalculation complete!" << endl;
        }
        pi_4 += sign * (1.0 / i);
        sign *= -1;
    }

    return pi_4;
}

double pi_async(long long int n, int num_threads) {
    long long int step = n / num_threads;
    vector<future<double>> futures;

    // Launch threads to compute different parts of the pi sum
    for (int i = 0; i < num_threads; ++i) {
        // long long int start = 1 + i * step * 2;
        // long long int end = (i == num_threads - 1) ? n : (i + 1) * step * 2;
        long long int start = (i == 0) ? 1 : i * step;
        long long int end = i * step + step - 1;        
        futures.push_back(async(launch::async, pi_partial, start, end));
    }

    // Aggregate the results from all threads
    double pi_4 = 0;
    for (auto& fut : futures) {
        pi_4 += fut.get();
    }
    cout << "Calculated pi is: ";
    return 4.0 * pi_4;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << " <n>" << " <threads> " << endl;
        return 1;
    }

    long long int n = stoll(argv[1]);
    int threads = atoi(argv[2]);
 
    auto start = chrono::high_resolution_clock::now();
 
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
 
    cout << fixed << setprecision(51) << pi_async(n, threads) << endl; 
 
    auto end = chrono::high_resolution_clock::now();
 
    // Calculating total time taken by the program.
    double time_taken = 
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
 
    time_taken *= 1e-9;
 
    cout << "Time taken by program is : " << fixed << setprecision(40) << time_taken;
    cout << " sec" << endl;
    return 0;
}
