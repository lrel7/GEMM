#include "omp.h"

// parallel using openmp
void mat_mul(double *a, double *b, double *c, int n){
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double temp = 0;
            for (int k = 0; k < n; k++) {
                temp += a[i * n + k] * b[k * n + j];
            }
            c[i * n + j] = temp;
        }
    }
}