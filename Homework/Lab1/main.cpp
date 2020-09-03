#include <iostream>
#include "grid2d.h"

using namespace std;

int main()
{
//    Grid2D grid;
    
    // start defining the grid
    int N = 3; // points in the x direction
    int M = 4; // points in the y direction

    // Domain : [xmin,xmax] by [ymin,ymax]
    // not a fan of putting my parameters here but whatever
    double xmin = 0.; // put dots at the end of the number to be safe
    double xmax = 2.;
    double ymin = 0.;
    double ymax = 2.;


    Grid2D new_grid(N,M,xmin,xmax,ymin,ymax);
     
    // the dot '.' is used to access the data members and the member functions of a class   
    cout << "Grid Resolution in x: " << new_grid.get_DX() << endl;

    cout << "Grid Resolution in y: " << new_grid.get_DY() << endl;
    
    int NM = N*M; // total number of grid points
    
    for (int n=0;n<NM;n++)
    {
        cout << "for n = " << n << ", i index is: " << new_grid.i_from_n(n) << endl;    
        cout << "\n";
    }

    for (int m=0;m<NM;m++)
    {
        cout << "for n = " << m << ", j index is: " << new_grid.j_from_n(m) << endl;    
        cout << "\n";
    }
    
    for (int j=0;j<M;j++)
    {
        for (int i=0;i<N;i++)
        {
            cout << i;
            cout << j; 
            cout << " Node is: "<< new_grid.n_from_ij(i,j) << endl;
        }
    }


    for (int n=0;n<NM;n++)
    {
        cout << "for n = " << n << ", x = " << new_grid.x_from_n(n) << " y = "<< new_grid.y_from_n(n) <<endl;    
        cout << "\n";
    }

    return(0);

}
