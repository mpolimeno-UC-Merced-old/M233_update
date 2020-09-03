#include <iostream>
#include <cmath>

using namespace std;

// testing some simple C++ routines

// function to compute the square of a number
double square(const double x)
{
    double y = x*x;
    return y;
}

// function to compute any power
double power(const double x, unsigned int n) // the way I wrote my main the second argument of power should not be const
{
    switch (n)
    {
        case 0 : return 1.; // raising to the zeroth power
        case 1 : return x; // raising to the first power
        case 2 : return square(x);
        default: // the default is the loop below
        {
            double f = x;
            for (int i=0; i<n; i++) f *= x;
            return f;
        }
    }
}

// main function
int main(void)
{   
    const double m = 5.;
    for (unsigned int i=0; i<5;i++)
    {        
        double res = power(m,i);    
        cout <<  res << endl;
        cout << "\n";
    }
    return 0;
}
