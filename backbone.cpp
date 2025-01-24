#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/function.h>
using namespace std;

class Vector {
    public:
        vector<double> elements;
        Vector(vector<double> elements) : elements(elements) {}
        Vector operator+(const Vector& other) const {
            vector<double> result;
            for (int i = 0; i < elements.size(); ++i) {
                result.push_back(elements[i] + other.elements[i]);
            }
            return Vector(result);
        }
        Vector operator-(const Vector& other) const {
            vector<double> result;
            for (int i = 0; i < elements.size(); ++i) {
                result.push_back(elements[i] - other.elements[i]);
            }
            return Vector(result);
        }
        double operator*(const Vector& other) const {
            double result = 0;
            for (int i = 0; i < elements.size(); ++i) {
                result += elements[i] * other.elements[i];
            }
            return result;
        }
        Vector operator*(double scalar) const {
            vector<double> result;
            for (int i = 0; i < elements.size(); ++i) {
                result.push_back(elements[i] * scalar);
            }
            return Vector(result);
        }
        Vector operator/(double scalar) const {
            vector<double> result;
            for (int i = 0; i < elements.size(); ++i) {
                result.push_back(elements[i] / scalar);
            }
            return Vector(result);
        }
        double& operator[](int index) {
            return elements[index];
        }
        int size() const {
            return elements.size();
        }
};

class Matrix {
    public:
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
        int size() const {
            return elements.size();
        }
};

class Predictor {
    public:
        virtual Vector predict(Vector input);
};

class LinearPredictor : public Predictor {
    public:
        Matrix weights;
        Vector bias;
        LinearPredictor(Matrix weights, Vector bias) : weights(weights), bias(bias) {}
        Vector predict(Vector input) {
            return weights * input + bias;
        }
};

Vector gradientDescent(function<double(Vector)> f, Vector params, Vector paramsPrev, double learningRate = 0.01, double alpha = 0.9) {
    Vector grad = Vector({});
    for (int i = 0; i < params.size(); ++i) {
        Vector inputPlus = params;
        inputPlus[i] += 0.001;
        Vector inputMinus = params;
        inputMinus[i] -= 0.001;
        grad.elements.push_back((f(inputPlus) - f(inputMinus)) / (2 * 0.001));
    }
    for (int j = 0; j < params.size(); ++j) {
        params[j] -= learningRate * grad[j] + alpha * (params[j] - paramsPrev[j]);
    }
    return params;
}