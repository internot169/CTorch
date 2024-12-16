#include <iostream>
using namespace std;

void printmatrix(float** matrix, int m, int n)
{
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printvector(float* vector, int n)
{
    for(int i = 0; i < n; i++){
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}


void rowReduction(float** matrix, int m, int n){
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

void inverse(float** matrix, int m, int n){
    if (m != n) {
        return;
    }
    float** inverse = new float*[m];
    for(int i = 0; i < m; i++){
        inverse[i] = new float[n * 2];
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

float* matrixVectorMultiplication(float** matrix, float* vector){
    if (sizeof(matrix[0]) != sizeof(vector) || sizeof(matrix[0]) == 0) {
        return nullptr;
    }

    float* result = new float[sizeof(matrix) / sizeof(matrix[0])];
    for (int i = 0; i < sizeof(matrix) / sizeof(matrix[0]); ++i) {
        result[i] = 0;
        for (int j = 0; j < sizeof(vector); ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
}

float** matrixMultiplication(float** matrix1, float** matrix2){
    if (sizeof(matrix1[0]) != sizeof(matrix2) || sizeof(matrix1[0]) == 0) {
        return nullptr;
    }

    float** result = new float*[sizeof(matrix1) / sizeof(matrix1[0])];
    for(int i = 0; i < sizeof(matrix1) / sizeof(matrix1[0]); i++){
        result[i] = new float[sizeof(matrix2[0])];
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

int determinant(float** matrix, int n){
    if (n == 1) {
        return matrix[0][0];
    }

    int det = 0;
    for (int i = 0; i < n; ++i) {
        float** submatrix = new float*[n - 1];
        for(int j = 0; j < n - 1; j++){
            submatrix[j] = new float[n - 1];
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

bool isEigenvalue(float** matrix, int lambda){
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

bool independent(float** matrix){
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

int rank(float** matrix){
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
    float** matrix = new float*[3];
    for(int i = 0; i < 3; i++){
        matrix[i] = new float[3];
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

    float** matb = new float*[3];
    for(int i = 0; i < 3; i++){
        matb[i] = new float[3];
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
    
    float* vector = new float[3];
    vector[0] = 1;
    vector[1] = 2;
    vector[2] = 3;

    cout << determinant(matrix, 3) << endl;
    
    return 0;
}