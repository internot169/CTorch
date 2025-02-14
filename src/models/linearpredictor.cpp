#include <iostream>
#include <functional>
#include <cmath>
#include "../backbone/vector.cpp"
#include "../backbone/matrix.cpp"
#include "predictor.cpp"
using namespace std;

class LinearPredictor: public Predictor {
    public:
        Vector weights;
        double bias;
        LinearPredictor(Vector weights, double bias) : weights(weights), bias(bias) {};
        Vector predict(Vector input) override {
            vector<double> out = {weights * input + bias};
            return Vector(out);
        };
        void fit(vector<Vector> X, vector<Vector> y, double learning_rate, int epochs, function<double(double)> loss) override {
            for (int epoch = 0; epoch < epochs; ++epoch) {
                vector<double> gradientEls(weights.size(), 0.0);
                Vector gradient(gradientEls);
                double bias_gradient = 0.0;
                double total_loss = 0.0;

                for (size_t i = 0; i < X.size(); ++i) {
                    Vector prediction = predict(X[i]);
                    Vector error = prediction - y[i];
                    for (size_t k = 0; k < error.size(); ++k) {
                        error[k] = loss(error[k]);
                        total_loss += error[k];
                    }

                    for (size_t j = 0; j < weights.size(); ++j) {
                        gradient[j] += error[0] * X[i][j];
                    }
                    bias_gradient += error[0];
                }

                for (size_t j = 0; j < weights.size(); ++j) {
                    weights[j] -= learning_rate * gradient[j] / X.size();
                }
                bias -= learning_rate * bias_gradient / X.size();

                cout << "Epoch " << epoch + 1 << "/" << epochs << ", Loss: " << total_loss / X.size() << endl;
            }
        };
};