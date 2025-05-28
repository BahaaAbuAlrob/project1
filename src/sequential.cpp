
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

using Matrix = vector<vector<int>>;

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

Matrix multiplySequential(const Matrix &A, const Matrix &B) {
    int n = A.size(), m = B[0].size(), p = B.size();
    Matrix C(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

int main() {
    int size = 500;
    Matrix A = generateMatrix(size, size);
    Matrix B = generateMatrix(size, size);

    auto start = high_resolution_clock::now();
    Matrix C = multiplySequential(A, B);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Sequential Execution Time: " << duration.count() << " ms" << endl;

    // checksum to validate result
    long long checksum = 0;
    for (const auto &row : C)
        for (int val : row)
            checksum += val;
    cout << "Checksum: " << checksum << endl;

    return 0;
}
