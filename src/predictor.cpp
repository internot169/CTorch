#include <iostream>
#include <functional>
#include <cmath>
#include "vector.cpp"
using namespace std;

class Predictor {
    public:
        virtual Vector predict(Vector input);
        virtual void fit(vector<Vector> X, vector<Vector> y, double learning_rate, int epochs, function<double(double)> loss);
};