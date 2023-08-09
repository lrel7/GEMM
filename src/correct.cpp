#include "iostream" 
#include "cstdlib"
#include "fstream"

#define N 2000

int main() {
    double *a = new double[N * N];
    double *b = new double[N * N];
    std::ifstream file_1("mat.txt");
    if (!file_1.is_open()) {
        std::cerr << "Error opening file for reading." << std::endl;
        return 1;
    }
    for(int i = 0; i < N; i++) {
        file_1 >> a[i];
    }
    for(int i = 0; i < N; i++) {
        file_1 >> b[i];
    }
    file_1.close();
    std::ofstream file_2("ans.txt");
    if(!file_2.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double temp = 0;
            for (int k = 0; k < N; k++) {
                temp += a[i * N + k] * b[k * N + j];
            }
            file_2 << std::fixed << std::setprecision(4) << temp << " ";
        }
    }
    file_2.close();
    delete[] a;
    delete[] b;
    return 0;
}
