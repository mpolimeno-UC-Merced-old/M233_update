#ifndef ENO_ADVECTION_H
#define ENO_ADVECTION_H

#include "grid2d.h"
#include <vector>

using namespace std;

class ENO_Advection
{
    private:
        vector<double> phi_n;
        double phinp;
        double phix;
        double phiy;
        double f1;
        double f2;
        Grid2D new_grid(int N_,int M_, double xmin_, double xmax_,double ymin_, double ymax_);
        double vx;
        double vy;
        double dt;
        double xmin;
        double xmax;
        double ymin;
        double ymax;
        int N;
        int Nsq;
        int n;     
    public:
        ENO_Advection();
        ENO_Advection(Grid2D new_grid,vector<double> &phi_n);    
        double xwind(Grid2D new_grid,vector<double> &phi_n,double vx,int n);
        double ywind(Grid2D new_grid,vector<double> &phi_n,double vy,int n);
        //double one_Step(Grid2D new_grid,double phinp,double phix,double phiy,double dt);
        double minmod(double f1,double f2);
        double one_Step(Grid2D new_grid,double u,double v,double phix,double phiy,vector<double> &phin,int n,double dt);
};
#endif // ENO_ADVECTION_H
