// compute 4 * 4 elements of C at a time
// TODO: generalize for n that is not a multiple of 4
void mat_mul(double * a, double *b, double *c, int n) {
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < n; j += 4) {
            for (int k = 0; k < n; k++) {
                // first col
                c[i * n + j] += a[i * n + k] * b[k * n + j];
                c[(i + 1) * n + j] += a[(i + 1) * n + k] * b[k * n + j];
                c[(i + 2) * n + j] += a[(i + 2) * n + k] * b[k * n + j];
                c[(i + 3) * n + j] += a[(i + 3) * n + k] * b[k * n + j];

                // second col
                c[i * n + j + 1] += a[i * n + k] * b[k * n + j + 1];
                c[(i + 1) * n + j + 1] += a[(i + 1) * n + k] * b[k * n + j + 1];
                c[(i + 2) * n + j + 1] += a[(i + 2) * n + k] * b[k * n + j + 1];
                c[(i + 3) * n + j + 1] += a[(i + 3) * n + k] * b[k * n + j + 1];

                // third col
                c[i * n + j + 2] += a[i * n + k] * b[k * n + j + 2];
                c[(i + 1) * n + j + 2] += a[(i + 1) * n + k] * b[k * n + j + 2];
                c[(i + 2) * n + j + 2] += a[(i + 2) * n + k] * b[k * n + j + 2];
                c[(i + 3) * n + j + 2] += a[(i + 3) * n + k] * b[k * n + j + 2];

                // forth col
                c[i * n + j + 3] += a[i * n + k] * b[k * n + j + 3];
                c[(i + 1) * n + j + 3] += a[(i + 1) * n + k] * b[k * n + j + 3];
                c[(i + 2) * n + j + 3] += a[(i + 2) * n + k] * b[k * n + j + 3];
                c[(i + 3) * n + j + 3] += a[(i + 3) * n + k] * b[k * n + j + 3];
            }
        }
    }
}
