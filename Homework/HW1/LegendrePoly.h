#ifndef LEGENDREPOLY_H
#define LEGENDREPOLY_H

#include <vector>

using namespace std;

class LegendrePoly
{

private:
    
    double x;
    int n;
        
    int N;
    double a, b;
    
public:
    
    LegendrePoly();
        
    double Legendre(double x, int n);
    vector<double> sampleLegendre(double a, double b, int N, int n);
};

#endif //LEGENDREPOLY_H
