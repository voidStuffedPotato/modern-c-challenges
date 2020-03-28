/*
 * Some of the most important problems for which arrays are used stem from
 * linear algebra. Can you write functions that do vector-to-vector or
 * matrix-to-vector products at this point? What about Gauss elimination or
 * iterative algorithms for matrix inversion?
 */

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

double **eye(size_t n);
void swap(size_t n, double a[n], double b[n]);
double scal_prod(size_t n, double a[n], double b[n]);
double *vec_to_mat(size_t m, size_t n, double vec[m], double arr[m][n]);
void vec_to_scal(size_t n, double a[n], double lambda);
void vec_w_sum(size_t n, double a[n], double b[n], double lambda);
int gauss_elimination(size_t m, size_t n, double arr[m][n]);
int inverse(size_t n, double[n][n], double*** inv);
double **mat_to_mat(size_t m, size_t n, size_t k, double A[m][n],
                    double B[n][k]);
void print_vec(size_t n, double* a);
void print_arr(size_t m, size_t n, double arr[m][n]);
void print_mat(size_t m, size_t n, double** mat);

int main() {
    double A[4][4] = {[0] = {1, 0, 1, 0},
                      [1] = {0, 0, 1, 0},
                      [2] = {0, 2, 1, 0},
                      [3] = {1, 4.5, 3, 1}
                     };
    double** inv = 0;
    int ret = inverse(4, A, &inv);
    if (ret == 0) {
        if (inv) {
            print_mat(4, 4, inv);
            free(inv);
        }
    }
    return 0;
}

void print_arr(size_t m, size_t n, double arr[m][n]) {
    puts("[");
    for (size_t i = 0; i < m; i++)
        print_vec(n, arr[i]);
    puts("]");
}

void print_vec(size_t n, double a[n]) {
    fputs("[", stdout);
    for (size_t i = 0; i < n; ++i)
        printf("%.3f%s", a[i], (i < n - 1) ? "\t" : "");
    puts("]");
}

void print_mat(size_t m, size_t n, double **arr) {
    puts("[");
    for (size_t i = 0; i < m; i++) {
        print_vec(n, arr[i]);
    }
    puts("]");
}

double scal_prod(size_t n, double a[n], double b[n]) {
    double res = 0;
    for (size_t i = 0; i < n; ++i)
        res += a[i] * b[i];
    return res;
}

double *vec_to_mat(size_t m, size_t n, double vec[m], double arr[m][n]) {
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

void vec_w_sum(size_t n, double a[n], double b[n], double lambda) {
    for (size_t i = 0; i < n; ++i)
        a[i] += lambda * b[i];
}

void vec_to_scal(size_t n, double a[n], double lambda) {
    for (size_t i = 0; i < n; ++i)
        a[i] *= lambda;
}

double **eye(size_t n) {
    double **ret_mat = calloc(n, sizeof(double *));
    for (size_t i = 0; i < n; ++i) {
        ret_mat[i] = calloc(n, sizeof(double));
    }
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

void swap(size_t n, double a[n], double b[n]) {
    for (size_t i = 0; i < n; ++i) {
        double tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

int gauss_elimination(size_t m, size_t n, double arr[m][n]) {
    for (size_t j = 0; j < n; ++j) {
        bool found = false;
        size_t nonzero = 0;
        for (size_t i = j; i < m; ++i) {
            if (arr[i][j] != 0) {
                found = true;
                nonzero = i;
                break;
            }
        }
        if (found) {
            swap(n, arr[j], arr[nonzero]);
            vec_to_scal(n, arr[j], arr[j][j] ? 1.0 / arr[j][j] : 1.0);
            for (size_t i = j + 1; i < n; ++i) {
                vec_w_sum(n, arr[i], arr[j], -1.0 * arr[i][j]);
            }
        } else
            return -1;
    }
    return 0;
}

double **mat_to_mat(size_t m, size_t n, size_t k, double A[m][n],
                    double B[n][k]) {
    double **ret_val = 0;
    ret_val = calloc(m, sizeof(double*));
    for (size_t i = 0; i < m; ++i)
        ret_val[i] = vec_to_mat(n, k, A[i], B);
    return ret_val;
}

int inverse(size_t n, double arr[n][n], double*** inv) {
    if (*inv) {
        free(*inv);
        *inv = 0;
    }
    *inv = eye(n);
    if (!(*inv)) {
        return -2;
    }
    // gauss_elimination for arr
    for (size_t j = 0; j < n; ++j) {
        bool found = false;
        size_t nonzero = 0;
        for (size_t i = j; i < n; ++i) {
            if (arr[i][j] != 0) {
                found = true;
                nonzero = i;
                break;
            }
        }
        if (found) {
            swap(n, arr[j], arr[nonzero]);
            swap(n, (*inv)[j], (*inv)[nonzero]);
            double curr = arr[j][j];
            vec_to_scal(n, arr[j], curr ? (1.0 / curr) : 1.0);
            vec_to_scal(n, (*inv)[j], curr ? (1.0 / curr) : 1.0);
            for (size_t i = j + 1; i < n; ++i) {
                curr = arr[i][j];
                vec_w_sum(n, arr[i], arr[j], -1.0 * arr[i][j]);
                vec_w_sum(n, (*inv)[i], (*inv)[j], -1.0 * curr);
            }
        } else
            return -1;
    }
    // transforming arr to E(n)
    for (size_t j = 1; j < n; ++j) {
        for (size_t i = 0; i < j; ++i) {
            double curr = arr[i][j];
            if (curr) {
                vec_w_sum(n, arr[i], arr[j], -1.0 * curr);
                vec_w_sum(n, (*inv)[i], (*inv)[j], -1.0 * curr);
            }
        }
    }
    return 0;
}
