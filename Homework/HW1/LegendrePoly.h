#ifndef LEGENDREPOLY_H
#define LEGENDREPOLY_H

#include <vector>

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
    std::vector<double> sampleLegendre(double a, double b, int N, int n);
};

#endif //LEGENDREPOLY_H
