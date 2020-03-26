/*
 *  Some of the most important problems for which arrays are uset stem from
 * linear algebra. Can you write functions that do vector-to-vector or
 * matrix-to-vector products at this point? What about Gauss elimination or
 * iterative algorithms for matrix inversion?
 * TODO: matrix inversion and Gauss elimination, tests
 */

#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

double scalprod(size_t n, double a[n], double b[n]);
double *vectomat(size_t m, size_t n, double vec[m], double arr[m][n]);
void vectorwsum(size_t n, double a[n], double b[n], double lambda);
void vectoscal(size_t n, double a[n], double lambda);
double **eye(size_t n);

int main() {}

double scalprod(size_t n, double a[n], double b[n]) {
    double res = 0;
    for (size_t i = 0; i < n; ++i)
        res += a[i] * b[i];
    return res;
}

double *vectomat(size_t m, size_t n, double vec[m], double arr[m][n]) {
    double *ret_vec = calloc(n, sizeof(double));
    if (ret_vec) {
        for (size_t i = 0; i < n; ++i) {
            double comp = 0.0;
            for (size_t k = 0; k < m; ++k) {
                comp += vec[k] * arr[k][i];
            }
            ret_vec[i] = comp;
        }
    }
    return ret_vec;
}

void vectorwsum(size_t n, double a[n], double b[n], double lambda) {
    for (size_t i = 0; i < n; ++i)
        a[i] += lambda * b[i];
}

void vectoscal(size_t n, double a[n], double lambda) {
    for (size_t i = 0; i < n; ++i)
        a[i] *= lambda;
}

double **eye(size_t n) {
    double **ret_mat = calloc(n, sizeof(double *) * n);
    if (ret_mat) {
        for (size_t i = 0; i < n; ++i)
            if (ret_mat[i])
                ret_mat[i][i] = 1;
            else {
                free(ret_mat);
                ret_mat = 0;
                break;
            }
    }
    return ret_mat;
}
