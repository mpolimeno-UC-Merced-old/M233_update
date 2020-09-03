#ifndef  GRID2D_H
#define GRID2D_H

class Grid2D
{

private:
    int N,M;
    
    double xmin,xmax;
    double ymin,ymax;
    
    double DX,DY;

//    int n = i + j*N;
//    int m = j + i*M;

public:
    Grid2D();
    Grid2D(int N_,int M_, double xmin_, double xmax_,double ymin_, double ymax_);    
    
    double get_DX();
    double get_DY();

    int i_from_n(int n_);
    int j_from_n(int n_);
    
    int n_from_ij(int i, int j);

    double x_from_n(int n_);
    double y_from_n(int n_);
};

#endif // GRID2D_H
