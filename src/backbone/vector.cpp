#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
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