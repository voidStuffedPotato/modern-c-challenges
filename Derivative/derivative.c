#include <stdio.h>
#include <math.h>

double F(double);
double f(double);

int main() {
   printf("sin 1/2 (derivative) = %.4f\n", f(0x2P-1));
   printf("sin 1/2 = %.4f\n", sin(-0x2P-1));
   return 0;
}

double f(double x){
    double delta_x = 0x1P-10;
    double left = (F(x + delta_x) - F(x)) / delta_x;
    double right = (F(x) - F(x - delta_x)) / delta_x;
    return (left + right) / 2;
}

double F(double x) {
    return cos(x);
}
