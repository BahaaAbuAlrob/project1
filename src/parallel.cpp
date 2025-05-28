
#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

using Matrix = vector<vector<int>>;

struct ThreadArgs {
    const Matrix *A;
    const Matrix *B;
    Matrix *C;
    int start_row;
    int end_row;
};

Matrix generateMatrix(int rows, int cols) {
    Matrix mat(rows, vector<int>(cols));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat[i][j] = dis(gen);
    return mat;
}

void* multiplyPart(void* arg) {
    ThreadArgs *args = (ThreadArgs*)arg;
    const Matrix &A = *(args->A);
    const Matrix &B = *(args->B);
    Matrix &C = *(args->C);
    int start = args->start_row;
    int end = args->end_row;
    int cols = B[0].size();
    int common = B.size();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < common; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return nullptr;
}

int main() {
    int size = 500;
    int num_threads = 4;

    Matrix A = generateMatrix(size, size);
    Matrix B = generateMatrix(size, size);
    Matrix C(size, vector<int>(size, 0));

    pthread_t threads[num_threads];
    ThreadArgs args[num_threads];
    int rows_per_thread = size / num_threads;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        args[i] = { &A, &B, &C, i * rows_per_thread, (i + 1) * rows_per_thread };
        if (i == num_threads - 1) args[i].end_row = size;
        pthread_create(&threads[i], nullptr, multiplyPart, &args[i]);
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Parallel Execution Time with " << num_threads << " threads: "
         << duration.count() << " ms" << endl;

    long long checksum = 0;
    for (const auto &row : C)
        for (int val : row)
            checksum += val;
    cout << "Checksum: " << checksum << endl;

    return 0;
}
