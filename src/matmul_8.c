#include <immintrin.h>
#include <omp.h>

typedef union {
    __m256d v;
    double d[4];
} vec;

inline int min(int a, int b) {
    return (a < b) ? a : b;
}

// rearrange A slice into col-major
void rearrangeA(double *a, double *a_, int n, int rows, int row_begin) {
    int idx = 0;
    for(int j = 0; j < n; j++) {
        a_[idx++] = a[row_begin * n + j];
        a_[idx++] = a[(row_begin + 1) * n + j];
        a_[idx++] = a[(row_begin + 2) * n + j];
        a_[idx++] = a[(row_begin + 3) * n + j];
    } 
}

void rearrangeB(double *b, double *b_, int n, int cols, int col_begin) {
    int idx = col_begin * n;
    for (int i = 0; i < n; i++) {
        b_[idx++] = b[i * n + col_begin];
        b_[idx++] = b[i * n + col_begin + 1];
        b_[idx++] = b[i * n + col_begin + 2];
        b_[idx++] = b[i * n + col_begin + 3];
    }
}

void inner_kernel(double *a, double *b, double *c, int rows, int cols, int row_begin, int col_begin, int n) {
    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < rows; i += 4) {
        double *a_ = new double[4 * n];
        rearrangeA(a, a_, n, rows, i);
        for (int j = 0; j < cols; j += 4) {
            // if (i == 0) {
                // rearrangeB(b, b_, n, cols, j);
            // }
            vec c_0, c_1, c_2, c_3, a_0, a_1, a_2, a_3, b_reg; 
            c_0.v = _mm256_setzero_pd();
            c_1.v = _mm256_setzero_pd();
            c_2.v = _mm256_setzero_pd();
            c_3.v = _mm256_setzero_pd();

            for (int k = 0; k < n; k++) {
                double t = a_[k * 4];
                // a_0.v = _mm256_set_pd(a[i * n + k], a[i * n + k], a[i * n + k], a[i * n + k]);
                a_0.v = _mm256_set_pd(t, t, t, t);
                t = a_[k * 4 + 1];
                // a_1.v = _mm256_set_pd(a[(i + 1) * n + k], a[(i + 1) * n + k], a[(i + 1) * n + k], a[(i + 1) * n + k]);
                a_1.v = _mm256_set_pd(t, t, t, t);
                t = a_[k * 4 + 2];
                // a_2.v = _mm256_set_pd(a[(i + 2) * n + k], a[(i + 2) * n + k], a[(i + 2) * n + k], a[(i + 2) * n + k]);
                a_2.v = _mm256_set_pd(t, t, t, t);
                t = a_[k * 4 + 3];
                // a_3.v = _mm256_set_pd(a[(i + 3) * n + k], a[(i + 3) * n + k], a[(i + 3) * n + k], a[(i + 3) * n + k]);
                a_3.v = _mm256_set_pd(t, t, t, t);
                b_reg.v = _mm256_loadu_pd((double*) &b[k * n + j + col_begin]);
                // first row
                c_0.v += a_0.v * b_reg.v;
                // second row
                c_1.v += a_1.v * b_reg.v;
                // third row
                c_2.v += a_2.v * b_reg.v;
                // fouth row
                c_3.v += a_3.v * b_reg.v;
            }
            c[(row_begin + i) * n + j + col_begin] += c_0.d[0];
            c[(row_begin + i) * n + j + 1 + col_begin] += c_0.d[1];
            c[(row_begin + i) * n + j + 2 + col_begin] += c_0.d[2];
            c[(row_begin + i) * n + j + 3 + col_begin] += c_0.d[3];
            c[(row_begin + i + 1) * n + j + col_begin] += c_1.d[0];
            c[(row_begin + i + 1) * n + j + 1 + col_begin] += c_1.d[1];
            c[(row_begin + i + 1) * n + j + 2 + col_begin] += c_1.d[2];
            c[(row_begin + i + 1) * n + j + 3 + col_begin] += c_1.d[3];
            c[(row_begin + i + 2) * n + j + col_begin] += c_2.d[0];
            c[(row_begin + i + 2) * n + j + 1 + col_begin] += c_2.d[1];
            c[(row_begin + i + 2) * n + j + 2 + col_begin] += c_2.d[2];
            c[(row_begin + i + 2) * n + j + 3 + col_begin] += c_2.d[3];
            c[(row_begin + i + 3) * n + j + col_begin] += c_3.d[0];
            c[(row_begin + i + 3) * n + j + 1 + col_begin] += c_3.d[1];
            c[(row_begin + i + 3) * n + j + 2 + col_begin] += c_3.d[2];
            c[(row_begin + i + 3) * n + j + 3 + col_begin] += c_3.d[3];
        }
    }
}

// compute 4 * 4 elements of C at a time using registers
// TODO: generalize for n that is not a multiple of 4
void mat_mul(double *a, double *b, double *c, int n) {
    const int block_size = 128;
    for (int i = 0; i < n; i += block_size) {
        const int rows = min(block_size, n - i);
        const int row_begin = i;
        // const int row_end = min(i + block_size, n);
        for (int j = 0; j < n; j += block_size) {
            const int cols = min(block_size, n - j);
            const int col_begin = j;
            // const int col_end = min(j + block_size, n);
            inner_kernel(&a[row_begin * n], b, c, rows, cols, row_begin, col_begin, n);
        }
    }
}
