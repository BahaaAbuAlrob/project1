#include <iostream>
#include <vector>
#include <fstream>
#include <random>

using namespace std;
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

void saveMatrix(const Matrix &mat, const string &filename) {
    ofstream out(filename);
    for (const auto &row : mat) {
        for (int val : row)
            out << val << " ";
        out << "\n";
    }
}

int main() {
    int size = 500;
    Matrix A = generateMatrix(size, size);
    Matrix B = generateMatrix(size, size);
    saveMatrix(A, "matrixA.txt");
    saveMatrix(B, "matrixB.txt");
    cout << "Matrices generated and saved.\n";
    return 0;
}