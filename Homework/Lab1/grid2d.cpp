#include "grid2d.h"

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
    DX = (xmax-xmin)/ (N-1.); // just add a dot afte the 1. so now you are dividing double/double
    DY = (ymax-ymin)/(M-1.);
}

// just checking if we are resolving the grid correctly
double Grid2D::get_DX()
{
    return DX;
}

double Grid2D::get_DY()
{
    return DY;
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
    double x = (n%N)*DX; // x_i = i*DX;
    return x;
}

// get y coordinate from node
double Grid2D::y_from_n(int n)
{
    double y = (n/N)*DY; // y_j = j*DX;
    return y;
}    
