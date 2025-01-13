#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
using namespace std;

// TODO: rewrite in terms of Matrix and Vector classes

void printmatrix(double** matrix, int m, int n)
{
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printvector(double* vector, int n)
{
    for(int i = 0; i < n; i++){
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}


void rowReduction(double** matrix, int m, int n){
    for (int i = 0; i < m; ++i) {
        int pivotRow = i;
        for (int j = i + 1; j < m; ++j) {
            if (abs(matrix[j][i]) > abs(matrix[pivotRow][i])) {
                pivotRow = j;
            }
        }

        if (pivotRow != i) {
            swap(matrix[i], matrix[pivotRow]);
        }

        double pivot = matrix[i][i];
        if (pivot != 0) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] /= pivot;
            }
        }

        for (int j = 0; j < m; ++j) {
            if (j != i) {
                double factor = matrix[j][i];
                for (int k = 0; k < n; ++k) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
            }
        }
    }
}

void inverse(double** matrix, int m, int n){
    if (m != n) {
        return;
    }
    double** inverse = new double*[m];
    for(int i = 0; i < m; i++){
        inverse[i] = new double[n * 2];
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            inverse[i][j] = matrix[i][j];
            if (i == j) {
                inverse[i][j + n] = 1;
            } else {
                inverse[i][j + n] = 0;
            }
        }
    }
    rowReduction(inverse, m, 2 * n);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = inverse[i][j + n];
        }
    }
}

double* matrixVectorMultiplication(double** matrix, double* vector){
    if (sizeof(matrix[0]) != sizeof(vector) || sizeof(matrix[0]) == 0) {
        return nullptr;
    }

    double* result = new double[sizeof(matrix) / sizeof(matrix[0])];
    for (int i = 0; i < sizeof(matrix) / sizeof(matrix[0]); ++i) {
        result[i] = 0;
        for (int j = 0; j < sizeof(vector); ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
}

double** matrixMultiplication(double** matrix1, double** matrix2){
    if (sizeof(matrix1[0]) != sizeof(matrix2) || sizeof(matrix1[0]) == 0) {
        return nullptr;
    }

    double** result = new double*[sizeof(matrix1) / sizeof(matrix1[0])];
    for(int i = 0; i < sizeof(matrix1) / sizeof(matrix1[0]); i++){
        result[i] = new double[sizeof(matrix2[0])];
    }
    for (int i = 0; i < sizeof(matrix1) / sizeof(matrix1[0]); ++i) {
        for (int j = 0; j < sizeof(matrix2[0]); ++j) {
            result[i][j] = 0;
            for (int k = 0; k < sizeof(matrix1[0]); ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

double dotProduct(double* vector1, double* vector2){
    if (sizeof(vector1) != sizeof(vector2) || sizeof(vector1) == 0) {
        return 0;
    }

    double result = 0;
    for (int i = 0; i < sizeof(vector1); ++i) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

int determinant(double** matrix, int n){
    if (n == 1) {
        return matrix[0][0];
    }

    int det = 0;
    for (int i = 0; i < n; ++i) {
        double** submatrix = new double*[n - 1];
        for(int j = 0; j < n - 1; j++){
            submatrix[j] = new double[n - 1];
        }
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (k < i) {
                    submatrix[j - 1][k] = matrix[j][k];
                } else if (k > i) {
                    submatrix[j - 1][k - 1] = matrix[j][k];
                }
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(submatrix, n - 1);
    }
    return det;
}

bool isEigenvalue(double** matrix, int lambda){
    for (int i = 0; i < sizeof(matrix) / sizeof(matrix[0]); ++i) {
        for (int j = 0; j < sizeof(matrix[0]); ++j) {
            if (i == j) {
                if (matrix[i][j] != lambda) {
                    return false;
                }
            } else {
                if (matrix[i][j] != 0) {
                    return false;
                }
            }
        }
    }
}

bool independent(double** matrix){
    rowReduction(matrix, sizeof(matrix) / sizeof(matrix[0]), sizeof(matrix[0]));
    for (int i = 0; i < sizeof(matrix) / sizeof(matrix[0]); ++i) {
        for (int j = 0; j < sizeof(matrix[0]); ++j) {
            if (matrix[i][j] != 1) {
                return false;
            }
        }
    }
    return true;
}

int rank(double** matrix){
    rowReduction(matrix, sizeof(matrix) / sizeof(matrix[0]), sizeof(matrix[0]));
    int rank = 0;
    for (int i = 0; i < sizeof(matrix) / sizeof(matrix[0]); ++i) {
        for (int j = 0; j < sizeof(matrix[0]); ++j) {
            if (matrix[i][j] == 1) {
                ++rank;
            }
        }
    }
    return rank;
}

int main()
{
    double** matrix = new double*[3];
    for(int i = 0; i < 3; i++){
        matrix[i] = new double[3];
    }
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 2;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 10;

    double** matb = new double*[3];
    for(int i = 0; i < 3; i++){
        matb[i] = new double[3];
    }
    matb[0][0] = 1;
    matb[0][1] = 2;
    matb[0][2] = 3;
    matb[1][0] = 0;
    matb[1][1] = 1;
    matb[1][2] = 2;
    matb[2][0] = 0;
    matb[2][1] = 0;
    matb[2][2] = 10;
    
    double* vector = new double[3];
    vector[0] = 1;
    vector[1] = 2;
    vector[2] = 3;

    cout << determinant(matrix, 3) << endl;
    
    return 0;
}