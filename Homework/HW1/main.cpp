#include <iostream>
#include <fstream>
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
    int N = 1000; // number of points in the interval
    double a = -1.; // lower bound
    double b = 1.; // upper bound
    int n = 5; // degree of Legendre Polynomial
    
    if (n<0 || n>5)
    {
        cout << "ERROR! We must have 0<=n<=5" << endl;
        exit(0);
    }
    
    char polyout[128];
    sprintf(polyout,"poly_%d.txt",n);

    ofstream res;
    res.open(polyout);

    vector<double> A = LP.sampledLegendre(a,b,N,n);
    

    for(int i=0;i<N;i++)
    {
        res << A[i] << endl;
    }
    res.close();

    return(0);
}
