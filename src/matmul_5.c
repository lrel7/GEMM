#include <immintrin.h>

typedef union {
    __m256d v;
    double d[4];
} vec;

// compute 4 * 4 elements of C at a time using registers
// TODO: generalize for n that is not a multiple of 4
void mat_mul(double *a, double *b, double *c, int n) {
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < n; j += 4) {
            vec c_0, c_1, c_2, c_3, a_0, a_1, a_2, a_3, b_reg; 
            c_0.v = _mm256_setzero_pd();
            c_1.v = _mm256_setzero_pd();
            c_2.v = _mm256_setzero_pd();
            c_3.v = _mm256_setzero_pd();

            for (int k = 0; k < n; k++) {
                a_0.v = _mm256_set_pd(a[i * n + k], a[i * n + k], a[i * n + k], a[i * n + k]);
                a_1.v = _mm256_set_pd(a[(i + 1) * n + k], a[(i + 1) * n + k], a[(i + 1) * n + k], a[(i + 1) * n + k]);
                a_2.v = _mm256_set_pd(a[(i + 2) * n + k], a[(i + 2) * n + k], a[(i + 2) * n + k], a[(i + 2) * n + k]);
                a_3.v = _mm256_set_pd(a[(i + 3) * n + k], a[(i + 3) * n + k], a[(i + 3) * n + k], a[(i + 3) * n + k]);
                b_reg.v = _mm256_loadu_pd((double*) &b[k * n + j]);
                // first row
                c_0.v += a_0.v * b_reg.v;
                // second row
                c_1.v += a_1.v * b_reg.v;
                // third row
                c_2.v += a_2.v * b_reg.v;
                // fouth row
                c_3.v += a_3.v * b_reg.v;
            }
            c[i * n + j] += c_0.d[0];
            c[i * n + j + 1] += c_0.d[1];
            c[i * n + j + 2] += c_0.d[2];
            c[i * n + j + 3] += c_0.d[3];
            c[(i + 1) * n + j] += c_1.d[0];
            c[(i + 1) * n + j + 1] += c_1.d[1];
            c[(i + 1) * n + j + 2] += c_1.d[2];
            c[(i + 1) * n + j + 3] += c_1.d[3];
            c[(i + 2) * n + j] += c_2.d[0];
            c[(i + 2) * n + j + 1] += c_2.d[1];
            c[(i + 2) * n + j + 2] += c_2.d[2];
            c[(i + 2) * n + j + 3] += c_2.d[3];
            c[(i + 3) * n + j] += c_3.d[0];
            c[(i + 3) * n + j + 1] += c_3.d[1];
            c[(i + 3) * n + j + 2] += c_3.d[2];
            c[(i + 3) * n + j + 3] += c_3.d[3];
        }
    }
}
