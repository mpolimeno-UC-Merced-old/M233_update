#include <iostream>
#include <vector>
#include "LegendrePoly.h"

using namespace std;

LegendrePoly::LegendrePoly()
{

}


double LegendrePoly::Legendre(double x, int n)
{
    
    int degree = n;
    double A; //return value
    
    switch(degree)
    {
        case 0:
            A = 1.; break;
        case 1:
            A = x; break;
        case 2:
            A =  0.5*(3.*x*x-1.); break;
        case 3:
            A = 0.5*(5.*x*x*x-3.*x); break;
        case 4:
            A = (1./8.)*(35.*x*x*x*x-30.*x*x+3); break;
        case 5:
            A = (1./8.)*(63.*x*x*x*x*x-70.*x*x*x+15*x); break;
        default: // for n<0 || n>5
            throw "ERROR! We must have 0<=n<=5";
    }
    return A;
}

vector<double> LegendrePoly::sampledLegendre(double a, double b, int N, int n)
{
    
    int degree = n;
    double xmin = a;
    double xmax = b;
    double dx = (xmax-xmin)/(N-1.);

    vector<double> x(N);

    for (int i=0;i<N;i++)
    {
        x[i] = xmin + i*dx;
    }
    
    vector<double> A(N);
    
    for(int i=0;i<N;i++)
    {
        switch(degree)
        {
            case 0:
                A[i] = 1.; break;
            case 1:
                A[i] = x[i]; break;
            case 2:
                A[i] =  0.5*(3.*x[i]*x[i]-1.); break;
            case 3:
                A[i] = 0.5*(5.*x[i]*x[i]*x[i]-3.*x[i]); break;
            case 4:
                A[i] = (1./8.)*(35.*x[i]*x[i]*x[i]*x[i]-30.*x[i]*x[i]+3); break;
            case 5:
                A[i] = (1./8.)*(63.*x[i]*x[i]*x[i]*x[i]*x[i]-70.*x[i]*x[i]*x[i]+15*x[i]); break;
            default:    
                break;
        }
    }
    return A;
}

