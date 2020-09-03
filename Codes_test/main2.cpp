#include <iostream>
#include <cmath>

using namespace std;

// trying mappings for dynamic allocation

void set_entry(double *M, double N[2][2],const int i, const int j, const int m, const double f)
{
    M[i*m + j] = f;
    N[i][j] = M[i*m+j]; //matrix to verify correct mapping
}

int main()
{
    const int n = 2; //number of rows
    const int m = 2; //number of cols
    
    double *M = new double[n*m];
    
    double N[2][2];

    set_entry(M,N,0,0,m,1.);
    set_entry(M,N,0,1,m,2.);
    set_entry(M,N,1,0,m,3.);
    set_entry(M,N,1,1,m,4.);

    // verify that the matrix is set correctly
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            cout << M[i*m+j] << " ";
        }
        cout << endl; // new row
    }
    
    cout << "\n";
    // verify that N and M are the same
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            cout << N[i][j] << " ";
        }
        cout << endl; // new row
    }
    return(0);
}
