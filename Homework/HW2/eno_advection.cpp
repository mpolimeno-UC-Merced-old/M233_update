#include <iostream>
#include "grid2d.h"
#include <math.h>
#include "eno_advection.h"
#include <vector>

using namespace std;

ENO_Advection::ENO_Advection(Grid2D new_grid,vector<double> &phin)
{
    int N = new_grid.get_N();
    phin.resize(N*N);
};

double ENO_Advection::xwind(Grid2D new_grid,vector<double> &phin,double u,int n)
{
    int N = new_grid.get_N();
    phin.resize(N*N);
    double fxm = new_grid.dx_backward(phin,n);
    double fxp = new_grid.dx_forward(phin,n);
    
    double phix;

    if (u==0.) phix = 0.;
    else
    {
        phix = (u>0.) ? u*fxm : u*fxp;
    }

    return phix;
}


double ENO_Advection::ywind(Grid2D new_grid,vector<double> &phin,double v,int n)
{
    int N = new_grid.get_N();
    phin.resize(N*N);
    double fym = new_grid.dy_backward(phin,n);
    double fyp = new_grid.dy_forward(phin,n);
    
    double phiy;

    if(v==0.) phiy = 0.;
    else
    {
        phiy = (v>0.) ? v*fym : v*fyp;
    }
    
    return phiy;
}


double ENO_Advection::minmod(double f1,double f2)
{
    double f;

    if(f1*f2<0.) f = 0.;
    else
    {
        f = (abs(f1)<=abs(f2)) ? f1 : f2;
    }
    return f;
}


double ENO_Advection::one_Step(Grid2D new_grid,double u,double v,double phix,double phiy,vector<double> &phin,int n,double dt)
{
    int N = new_grid.get_N();
    phin.resize(N*N);

    double xval = new_grid.x_from_n(n);
    double yval = new_grid.y_from_n(n);
    double xmin = new_grid.get_xmin();
    double xmax = new_grid.get_xmax();
    double ymin = new_grid.get_ymin();
    double ymax = new_grid.get_ymax();

    double dx = new_grid.get_dx();
    double dy = new_grid.get_dy();
    double vdotgrad = phix + phiy;

    double xmod;
    double ymod;

    if (u==0.) xmod = 0.;
    else
    {
        if(xval==xmin) 
        {
            xmod = (u>0.) ? u*minmod(new_grid.dxx_backward(phin,n),new_grid.dxx_backward(phin,n+1)) : u*minmod(new_grid.dxx_forward(phin,n),new_grid.dxx_forward(phin,n+1));
        }
        else if (xval==xmax) 
        {
            xmod = (u>0.) ? u*minmod(new_grid.dxx_backward(phin,n),new_grid.dxx_backward(phin,n-1)) : u*minmod(new_grid.dxx_forward(phin,n),new_grid.dxx_forward(phin,n-1));
        }
        else
        {
            xmod = (u>0.) ? u*minmod(new_grid.dxx_backward(phin,n),new_grid.dxx_backward(phin,n-1)) : u*minmod(new_grid.dxx_forward(phin,n),new_grid.dxx_forward(phin,n+1));
        } 
    }
    
    if (v==0.) ymod = 0.;
    else
    {
        if(yval==ymin) 
        {
            ymod = (v>0.) ? v*minmod(new_grid.dyy_backward(phin,n),new_grid.dyy_backward(phin,n+N)) : v*minmod(new_grid.dyy_forward(phin,n),new_grid.dyy_forward(phin,n+N));
        }
        else if (yval==ymax) 
        {
            ymod = (v>0.) ? v*minmod(new_grid.dyy_backward(phin,n),new_grid.dyy_backward(phin,n-N)) : v*minmod(new_grid.dyy_forward(phin,n),new_grid.dyy_forward(phin,n-N));
        }
        else
        {
            ymod = (v>0.) ? v*minmod(new_grid.dyy_backward(phin,n),new_grid.dyy_backward(phin,n-N)) : v*minmod(new_grid.dyy_forward(phin,n),new_grid.dyy_forward(phin,n+N));
        }
    } 
    
    double hot = (0.5*xmod*dx)+(0.5*ymod*dy);

    double fup = vdotgrad*dt + hot*dt;
    
    double phinp = phin[n];

    double phinp1;

    phinp1 = phinp - fup; 
    
    return phinp1;
}

/*
double ENO_Advection::one_Step(Grid2D new_grid,double phinp,double phix,double phiy,double dt)
{
    int N = new_grid.get_N();
    double vdotgrad = phix + phiy;
    double fup = vdotgrad*dt;

    double phinp1;
    phinp1 = phinp - fup; 
    
    return phinp1;
}
*/
