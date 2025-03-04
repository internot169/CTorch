#include <iostream>
#include <functional>
#include <cmath>
#include "vector.cpp"
using namespace std;



struct Matrix {
    
    vector<vector<double>> elements;
    Matrix(vector<vector<double>> elements) : elements(elements) {}
    Matrix operator+(const Matrix& other) const {
        vector<vector<double>> result;
        for (int i = 0; i < elements.size(); ++i) {
            vector<double> row;
            for (int j = 0; j < elements[i].size(); ++j) {
                row.push_back(elements[i][j] + other.elements[i][j]);
            }
            result.push_back(row);
        }
        return Matrix(result);
    }
    Matrix operator-(const Matrix& other) const {
        vector<vector<double>> result;
        for (int i = 0; i < elements.size(); ++i) {
            vector<double> row;
            for (int j = 0; j < elements[i].size(); ++j) {
                row.push_back(elements[i][j] - other.elements[i][j]);
            }
            result.push_back(row);
        }
        return Matrix(result);
    }
    Matrix operator*(const Matrix& other) const {
        vector<vector<double>> result;
        for (int i = 0; i < elements.size(); ++i) {
            vector<double> row;
            for (int j = 0; j < other.elements[0].size(); ++j) {
                double sum = 0;
                for (int k = 0; k < elements[i].size(); ++k) {
                    sum += elements[i][k] * other.elements[k][j];
                }
                row.push_back(sum);
            }
            result.push_back(row);
        }
        return Matrix(result);
    }
    Matrix operator*(const double scalar) const {
        vector<vector<double>> result;
        for (int i = 0; i < elements.size(); ++i) {
            vector<double> row;
            for (int j = 0; j < elements[i].size(); ++j) {
                row.push_back(elements[i][j] * scalar);
            }
            result.push_back(row);
        }
        return Matrix(result);
    }
    Vector operator*(const Vector& other) const {
        Vector result = Vector({}); 
        for (int i = 0; i < elements.size(); ++i) {
            double sum = 0;
            for (int j = 0; j < elements[i].size(); ++j) {
                sum += elements[i][j] * other.elements[j];
            }
            result.elements.push_back(sum);
        }
        return result;
    }
    vector<double>& operator[](int index) {
        return elements[index];
    }
    Matrix transpose() const {
        vector<vector<double>> result;
        for (int i = 0; i < elements[0].size(); ++i) {
            vector<double> row;
            for (int j = 0; j < elements.size(); ++j) {
                row.push_back(elements[j][i]);
            }
            result.push_back(row);
        }
        return Matrix(result);
    }
    int size() const {
        return elements.size();
    }
};
