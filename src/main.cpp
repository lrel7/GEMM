#include "benchmark/benchmark.h"
#include "cstdlib"
#include <iostream>
#include <ostream>
#include <cstring>
#include "fstream"

#define N 2000

void read_mat(double *a, double *b) {
    std::ifstream file("mat.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }
    for(int i = 0; i < N; i++) {
        file >> a[i];
    }
    for(int i = 0; i < N; i++) {
        file >> b[i];
    }
}

void mat_mul(double *a, double *b, double *c, int n);
bool test_result(double *c, int n);

static void matmul_benchmark(benchmark::State &s) {
    double *a = new double[N * N];
    double *b = new double[N * N];
    double *c = new double[N * N];
    memset(c, 0, sizeof(double) * N * N); 
    read_mat(a, b);
    for (auto _: s) {
        mat_mul(a, b, c, N);
    }
    if (test_result(c, N)) {
        std::cout << "Correct!" << std::endl;
    }
    else {
        std::cout << "Uncorrect!" << std::endl;
    }
    delete[] a;
    delete[] b;
    delete[] c;
}

BENCHMARK(matmul_benchmark)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();


