import numpy as np
from matplotlib import pyplot as plt

N = 1000;
x = np.linspace(-1.,1.,N);


poly0 = np.loadtxt("poly_0.txt");
poly1 = np.loadtxt("poly_1.txt");
poly2 = np.loadtxt("poly_2.txt");
poly3 = np.loadtxt("poly_3.txt");
poly4 = np.loadtxt("poly_4.txt");
poly5 = np.loadtxt("poly_5.txt");


plt.plot(x,poly0,'g-',label='$A^{0}_{1000}$',linewidth=2);
plt.plot(x,poly1,'b-',label='$A^{1}_{1000}$',linewidth=2);
plt.plot(x,poly2,'c-',label='$A^{2}_{1000}$',linewidth=2);
plt.plot(x,poly3,'r-',label='$A^{3}_{1000}$',linewidth=2);
plt.plot(x,poly4,'y-',label='$A^{4}_{1000}$',linewidth=2);
plt.plot(x,poly5,'m-',label='$A^{5}_{1000}$',linewidth=2);
plt.xlim([-1.,1.])
plt.ylim([-1.25,1.25])
plt.xlabel('$x$',fontsize=15)
plt.ylabel('$A^{n}_{N}(x)$',fontsize=15)
plt.title('Legendre Polynomials',fontsize=15)
plt.grid()
plt.legend(loc='lower right')
plt.show()
