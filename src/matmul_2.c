// compute 4 elements of C at a time
// improved the locality of B
// TODO: generalized for n that is not a multiple of 4
void mat_mul(double *a, double *b, double *c, int n) {
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
                c[(i + 1) * n + j] += a[(i + 1) * n + k] * b[k * n + j];
                c[(i + 2) * n + j] += a[(i + 2) * n + k] * b[k * n + j];
                c[(i + 3) * n + j] += a[(i + 3) * n + k] * b[k * n + j];
            }
        }
    }
}
