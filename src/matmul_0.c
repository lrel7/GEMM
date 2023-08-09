// serial
void mat_mul(double *a, double *b, double *c, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double temp = 0;
            for (int k = 0; k < n; k++) {
                // c[i * n + j] += a[i * n + k] * b[k * n + j];
                temp += a[i * n + k] * b[k * n + j];
            }
            c[i * n + j] = temp;
        }
    }
}
