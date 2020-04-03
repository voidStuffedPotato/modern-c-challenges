/*
 * Can you extend the real and complex derivatives such that they receive the function F
 * And the value x as a parameter?
 * Can tou use the generic real derivatives to implement Newton's method for finding roots?
 * Can you find the real zeros of polynomials?
 * Can you find complex zeros of polynomials?
 */

#include <stdio.h>
#include <math.h>

#define EPS 0x1p-10

double derivative(double, double F(double));
double second(double x);
double newton(double x, double F(double x));
double third(double x);

int main() {
    printf("second'(%f) = %f\n", 5.0, derivative(5.0, second));
    printf("root of third = %f\n", newton(4, third));
    return 0;
}

double derivative(double x, double F(double)){
    double delta_x = 0x1P-10;
    double left = (F(x + delta_x) - F(x)) / delta_x;
    double right = (F(x) - F(x - delta_x)) / delta_x;
    return (left + right) / 2;
}

double newton(double x, double F(double x)) {
    double curr, prev;
    curr = x;
    do {
        prev = curr;
        curr = prev - F(curr)/derivative(prev, F);
    } while (fabs(curr - prev) > EPS);
    return curr;
}

double third(double x) {
    return x * (x - 3) * (x + 2) * (x - 4.33);
}

double second(double x) {
    return x * x;
}
