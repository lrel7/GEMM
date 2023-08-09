#include "algorithm"
#include "random"
#include "cstdlib"
#include "iostream"
#include "fstream"

#define N 2000

int main(void) {
    std::ofstream file("mat.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1;
    }

    // config random generator
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<double> dist(-10, 10);

    // matrix A and B
    for(int i = 0; i < 2 * N * N; i++) {
        file << std::fixed << std::setprecision(4) << dist(rng) << " ";
    }
    file.close();
}
