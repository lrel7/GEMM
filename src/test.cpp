#include "iostream"
#include "fstream"
#include "cmath"

bool test_result(double *c, int n) {
    std::ifstream file("../data/ans.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading." << std::endl;
        return false;
    }
    double temp = 0;
    for (int i = 0; i < n * n ; i++) {
        file >> temp;
        if (std::abs(temp - c[i]) > 1e-3) {
            printf("The %d-th element should be %.4lf not %.4lf\n", i, temp, c[i]);
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}
