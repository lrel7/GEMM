// compute 4 * 4 elements of C at a time using registers
// TODO: generalize for n that is not a multiple of 4
void mat_mul(double * a, double *b, double *c, int n) {
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < n; j += 4) {
            register double c_00 = 0, c_01 = 0, c_02 = 0, c_03 = 0, c_10 = 0, c_11 = 0, c_12 = 0, c_13 = 0, c_20 = 0, c_21 = 0, c_22 = 0, c_23 = 0, c_30 = 0, c_31 = 0, c_32 = 0, c_33 = 0, a_0, a_1, a_2, a_3;
            for (int k = 0; k < n; k++) {
                a_0 = a[i * n + k];
                a_1 = a[(i + 1) * n + k];
                a_2 = a[(i + 2) * n + k];
                a_3 = a[(i + 3) * n + k];
                
                // first col
                c_00 += a_0 * b[k * n + j];
                c_10 += a_1 * b[k * n + j];
                c_20 += a_2 * b[k * n + j];
                c_30 += a_3 * b[k * n + j];

                // second col
                c_01 += a_0 * b[k * n + j + 1];
                c_11 += a_1 * b[k * n + j + 1];
                c_21 += a_2 * b[k * n + j + 1];
                c_31 += a_3 * b[k * n + j + 1];

                // third col
                c_02 += a_0 * b[k * n + j + 2];
                c_12 += a_1 * b[k * n + j + 2];
                c_22 += a_2 * b[k * n + j + 2];
                c_32 += a_3 * b[k * n + j + 2];

                // forth col
                c_03 += a_0 * b[k * n + j + 3];
                c_13 += a_1 * b[k * n + j + 3];
                c_23 += a_2 * b[k * n + j + 3];
                c_33 += a_3 * b[k * n + j + 3];
            }
            c[i * n + j] = c_00;
            c[i * n + j + 1] = c_01;
            c[i * n + j + 2] = c_02;
            c[i * n + j + 3] = c_03;
            c[(i + 1) * n + j] = c_10;
            c[(i + 1) * n + j + 1] = c_11;
            c[(i + 1) * n + j + 2] = c_12;
            c[(i + 1) * n + j + 3] = c_13;
            c[(i + 2) * n + j] = c_20;
            c[(i + 2) * n + j + 1] = c_21;
            c[(i + 2) * n + j + 2] = c_22;
            c[(i + 2) * n + j + 3] = c_23;
            c[(i + 3) * n + j] = c_30;
            c[(i + 3) * n + j + 1] = c_31;
            c[(i + 3) * n + j + 2] = c_32;
            c[(i + 3) * n + j + 3] = c_33;
        }
    }
}
