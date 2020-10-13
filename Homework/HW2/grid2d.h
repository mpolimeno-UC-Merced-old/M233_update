#ifndef  GRID2D_H
#define GRID2D_H
#include <vector>

using namespace std;
class Grid2D
{

private:
    int N,M;
    
    double xmin,xmax;
    double ymin,ymax;
    
    double dx,dy;

//    int n = i + j*N;
//    int m = j + i*M;

public:
    Grid2D();
    Grid2D(int N_,int M_, double xmin_, double xmax_,double ymin_, double ymax_);    
    
    void initialize_VTK_file(std::string file_name);    
    void print_VTK_Format( std::vector<double> &F, std::string data_name, std::string file_name );

    double get_dx();
    double get_dy();
    double get_xmin();
    double get_xmax();
    double get_ymin();
    double get_ymax();
    int get_N();
    int i_from_n(int n_);
    int j_from_n(int n_);
    
    int n_from_ij(int i, int j);

    double x_from_n(int n_);
    double y_from_n(int n_);
    double dx_forward(vector<double>& function,int n);
    double dx_backward(vector<double>& function,int n);
    double dy_forward(vector<double>& function,int n);
    double dy_backward(vector<double>& function,int n);

    double dxx_forward(vector<double> & function,int n);
    double dxx_backward(vector<double> & function,int n);
    double dyy_forward(vector<double> & function,int n);
    double dyy_backward(vector<double> & function,int n);
};

#endif // GRID2D_H
