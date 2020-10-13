#include <iostream>
#include <math.h>
#include "cf_2.h"
#include "grid2d.h"
#include "eno_advection.h"
#include <vector>

#define Pi acos(-1.)

using namespace std;

int main()
{
    class velocity_X: public CF_2
    {
        public:
            double operator()(double x, double y) const{
    
        return -1.*y;
    }
    };

    class velocity_Y: public CF_2
    {
        public:
            double operator()(double x, double y) const{

        return x;
    }
    };
    
    int N = 512;
    int Nsq = N*N;

    double xmin = -1.;
    double xmax = 1.;
    double ymin = -1.;
    double ymax = 1.;
    
    double dx = (xmax-xmin)/(N-1.);
    double dy = (ymax-ymin)/(N-1.);
    velocity_X vx;
    velocity_Y vy;

    
    Grid2D new_grid(N,N,xmin,xmax,ymin,ymax);
    

    vector<double> phin;
    phin.resize(Nsq);
    
    for (int n=0;n<Nsq;n++)
    {
        double x = new_grid.x_from_n(n);
        double y = new_grid.y_from_n(n);
        //phin[n] = sqrt(((x-0.25)*(x-0.25))+(y*y))-0.2;
        if(sqrt(((x-0.5)*(x-0.5))+(y*y))-0.2<=0.) phin[n] = 1.;
        else phin[n] = 0.;
    }


    double dt = 0.25*dx;
    vector<double> sols;
    sols.resize(N*N);

    ENO_Advection eno(new_grid,phin);


    char vtkfile[250];
    sprintf(vtkfile,"sol_eno_N_%d_t_%d.vtk",N,0); // initial data for movies in paraview
    new_grid.initialize_VTK_file(vtkfile);
    new_grid.print_VTK_Format(phin,"values_at_nodes",vtkfile); // for movies in paraview
    
    char filename[128];
    sprintf(filename,"sol_MATLAB_N_%d_t_%d.DAT",N,0);

    FILE *fp = fopen(filename,"w");
    for (int n=0;n<Nsq;n++)
    {
        fprintf(fp,"%g\t",phin[n]); // for matlab initial solution
    }
    fclose(fp);

    char filename2[128];
    char vtkfile2[250];
    int k = 1;
    double tn = 0.;


    double xval;
    double yval;
    double phix;
    double phiy;
    double phinp1;

    while(tn<=2.*Pi)
    {

        if (tn+dt>2.*Pi) tn = 2.*Pi;
        
        for (int n=0;n<Nsq;n++)
        {
            xval = new_grid.x_from_n(n);
            yval = new_grid.y_from_n(n);
            phix = eno.xwind(new_grid,phin,vx(xval,yval),n); 
            phiy = eno.ywind(new_grid,phin,vy(xval,yval),n);
            phinp1 = eno.one_Step(new_grid,vx(xval,yval),vy(xval,yval),phix,phiy,phin,n,dt);
            phin[n] = phinp1;            
        }

        sprintf(vtkfile2,"sol_eno_N_%d_t_%d.vtk",N,k);
        new_grid.initialize_VTK_file(vtkfile2);
        new_grid.print_VTK_Format(phin,"values_at_nodes",vtkfile2); // for movies in paraview
        
        // get final data for matlab
        
        if (tn==2.*Pi)
        {
            sprintf(filename2,"sol_MATLAB_N_%d_t_%d.DAT",N,k);
            FILE *fp2 = fopen(filename2,"w");
            for (int n=0;n<Nsq;n++)
            {
                fprintf(fp2,"%g\t",phin[n]);
            }
            fclose(fp2);
        }
        
        tn = tn + dt;
        k = k + 1;
    }
    return 0;
}
