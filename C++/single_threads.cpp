#include<iostream>
#include<iomanip>
#include<cmath>
#include<math.h>

using namespace std;

double pi1(int n) {
    double sum = 0.0;
    int sign = 1;
    for (int i = 0; i < n; ++i) {           
        sum += sign/(2.0*i+1.0);
        sign *= -1;
    }
    return 4.0*sum;
}

double pi2(long long int n) {
    double pi_4 = 0;
    int sign = 1;
    long long int i = 0;
    int percent = 0;
    long long int step = n/100;

    for (i = 1; i < n; i += 2)
    {
        if (i % step == 1) {
            percent++;
            cout << '\r' << "Progress: " << percent << "% " << flush;

        }
        if (sign)
        {
            pi_4 += 1.0 / i;
            sign = 0;
        }
        else
        {
            pi_4 -= 1.0 / i;
            sign = 1;
        }
    }
    cout << "complete" << endl;
    return 4*pi_4;
}


int main(int argc, char* argv[])  
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number>" << endl;
        return 1; // Return an error code
    }
    //declare variables
    double sum, pi;
    long long int n = stoll(argv[1]);
    
    //prompt user
    // cout << "How many decimals would you like to calculate pi to? ";
    // cin >> n;
    
    //calculate pi
    
    //print response
    cout << fixed << setprecision(51) << pi2(n) << endl;

    return 0;
}

