#include <iostream>
#include <vector>
#include "LegendrePoly.h"

// HW1 for M233, Fall2020
using namespace std;

int main()
{
    LegendrePoly LP;

    // for Legendre
    double x = 2.; // sample x value

    for (int n=-1;n<7;n++)
    {
        try
        {
            cout << LP.Legendre(x,n) << endl;
        }   
        catch (const char *msg)
        { // since the exception is of type const char*
            cerr << msg << endl;
        }
    }

    // for sampleLegendre
    int N = 5; // number of point in the interval
    double a = -1.; // left bound
    double b = 1.; // right bound
    int n = 4; // degree of Legendre Polynomial
    
    vector<double> A = LP.sampleLegendre(a,b,N,n);
    
    if (n<0 || n>5)
    {
        cout << "ERROR! We must have 0<n<5" << endl;
        exit(0);
    }

    for(int i=0;i<N;i++)
    {
        cout << A[i] << endl;
    }
    return(0);
}
