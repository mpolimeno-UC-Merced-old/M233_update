#include "grid2d.h"
#include <vector>
using namespace std;
/*
Grid2D::Grid2D()
{

}
*/

Grid2D::Grid2D(int N_,int M_,double xmin_,double xmax_,double ymin_,double ymax_)//all the paramenters
{
    // unneccessary really, but better to be safe than sorry, I guess
    N = N_;
    M = M_;
    xmin = xmin_;
    xmax = xmax_;
    ymin = ymin_;
    ymax = ymax_;


    // if you are doing double/int most compilers will return double anyways
    dx = (xmax-xmin)/ (N-1.); // just add a dot afte the 1. so now you are dividing double/double
    dy = (ymax-ymin)/(M-1.);
}

// just checking if we are resolving the grid correctly

double Grid2D::get_xmin()
{
    return xmin;
}

double Grid2D::get_xmax()
{
    return xmax;
}

double Grid2D::get_ymin()
{
    return ymin;
}

double Grid2D::get_ymax()
{
    return ymax;
}

double Grid2D::get_dx()
{
    return dx;
}

double Grid2D::get_dy()
{
    return dy;
}

int Grid2D::get_N()
{
    return N;
}
// indices (i,j)
// get i index from the node number n
int Grid2D::i_from_n(int n)
{
    // n = i + j*N
    
    int i = n % N;
    return i; 
}

    
// get j index from the node number n
int Grid2D::j_from_n(int n)
{
    // n = j + i*M
    
    int j = n/N; // n divided by the number of rows // returns floor(int), which is j index
    return j; 
}

int Grid2D::n_from_ij(int i, int j)
{
    int n = i + j*N;
    return n;
}

// get x coordinate from node
double Grid2D::x_from_n(int n)
{
    double x = xmin + (n%N)*dx; // x_i = i*dx;
    return x;
}

// get y coordinate from node
double Grid2D::y_from_n(int n)
{
    double y = ymin + (n/N)*dy; // y_j = j*dx;
    return y;
}

double Grid2D::dx_forward(vector<double> & function,int n)
{
    function.resize(N*N);
    double xval = x_from_n(n);
    double Fxp;
    
    if (xval==xmin || xval==xmax) Fxp = 0.;
    else Fxp = (function[n+1]-function[n])/dx;
    return Fxp;
}

double Grid2D::dx_backward(vector<double> & function,int n)
{
    function.resize(N*N);
    double xval = x_from_n(n);
    double Fxm;
    
    if (xval==xmin || xval==xmax) Fxm = 0.;
    else Fxm = (function[n]-function[n-1])/dx;
    
    return Fxm;
}

double Grid2D::dy_forward(vector<double> & function,int n)
{
    function.resize(N*N);
    double yval = y_from_n(n);
    double Fyp;
    
    if (yval==ymin || yval==ymax) Fyp = 0.;
    else Fyp = (function[n+N]-function[n])/dy;
    
    return Fyp;
}

double Grid2D::dy_backward(vector<double> & function,int n)
{
    function.resize(N*N);
    double yval = y_from_n(n);
    double Fym;
    
    if (yval==ymin || yval==ymax) Fym = 0.;
    else Fym = (function[n]-function[n-N])/dy;
    
    return Fym;
}    
    
double Grid2D::dxx_forward(vector<double> & function,int n)
{
    double xval = x_from_n(n);
    double yval = y_from_n(n);
    double Fxxp;

    if (xval==xmin && yval==ymin) Fxxp = 0.;
    else if (xval==xmin && yval==ymax) Fxxp = 0.;
    else if (xval==xmax && yval==ymin) Fxxp = 0.;
    else if (xval==xmax && yval==ymax) Fxxp = 0.;
    else Fxxp = (dx_forward(function,n)-dx_backward(function,n))/(dx);
    return Fxxp;
}

double Grid2D::dxx_backward(vector<double> & function,int n)
{
    double xval = x_from_n(n);
    double yval = y_from_n(n);
    double Fxxm;

    if (xval==xmin && yval==ymin) Fxxm = 0.;
    else if (xval==xmin && yval==ymax) Fxxm = 0.;
    else if (xval==xmax && yval==ymin) Fxxm = 0.;
    else if (xval==xmax && yval==ymax) Fxxm = 0.;
    else Fxxm = (dx_forward(function,n)-dx_backward(function,n))/(dx);
    return Fxxm;
}

double Grid2D::dyy_forward(vector<double> & function,int n)
{
    double xval = x_from_n(n);
    double yval = y_from_n(n);
    double Fyyp;
    
    if (xval==xmin && yval==ymin) Fyyp = 0.;
    else if (xval==xmin && yval==ymax) Fyyp = 0.;
    else if (xval==xmax && yval==ymin) Fyyp = 0.;
    else if (xval==xmax && yval==ymax) Fyyp = 0.;
    else Fyyp = (dy_forward(function,n)-dy_backward(function,n))/(dy);
    return Fyyp;
}

double Grid2D::dyy_backward(vector<double> & function,int n)
{
    double xval = x_from_n(n);
    double yval = y_from_n(n);
    double Fyym;
    
    
    if (xval==xmin && yval==ymin) Fyym = 0.;
    else if (xval==xmin && yval==ymax) Fyym = 0.;
    else if (xval==xmax && yval==ymin) Fyym = 0.;
    else if (xval==xmax && yval==ymax) Fyym = 0.;
    else Fyym = (dy_forward(function,n)-dy_backward(function,n))/(dy);
    return Fyym;
}
    
