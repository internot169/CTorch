#include <iostream>
#include <functional>
#include <cmath>
#include "vector.cpp"
#include "matrix.cpp"
#include "predictor.cpp"
using namespace std;


struct NeuralNetwork {
    
    vector<Matrix> weights;
    vector<Vector> biases;
    vector<function<double(double)>> activations;
    NeuralNetwork(vector<Matrix> weights, vector<Vector> biases, vector<function<double(double)>> activations) : weights(weights), biases(biases), activations(activations) {};
    Vector predict(Vector input)  {
        Vector result = input;
        for (int i = 0; i < weights.size(); ++i) {
            result = weights[i] * result + biases[i];
            for (int j = 0; j < result.size(); ++j) {
                result[j] = activations[i](result[j]);
            }
        }
        return result;
    };
    void fit(vector<Vector> X, vector<Vector> y, double learning_rate, int epochs, function<double(double)> loss)  {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            double total_loss = 0.0;
            for (int i = 0; i < X.size(); ++i) {
                Vector input = X[i];
                Vector target = y[i];
                vector<Vector> outputs = {input};
                for (int j = 0; j < weights.size(); ++j) {
                    Vector output = weights[j] * input + biases[j];
                    for (int k = 0; k < output.size(); ++k) {
                        output[k] = activations[j](output[k]);
                    }
                    outputs.push_back(output);
                    input = output;
                }

                Vector error = outputs.back() - target;
                double loss_value = 0.0;
                for (int k = 0; k < error.size(); ++k) {
                    loss_value += loss(error[k]);
                }
                total_loss += loss_value;

                for (int j = weights.size() - 1; j >= 0; --j) {
                    Vector output = outputs[j + 1];
                    Vector input = outputs[j];
                    Vector delta = Vector({});
                    for (int k = 0; k < output.size(); ++k) {
                        delta.elements.push_back(error[k] * activations[j](output[k]));
                    }
                    Matrix weight_deltas = Matrix({});
                    for (int k = 0; k < delta.size(); ++k) {
                        vector<double> row;
                        for (int l = 0; l < input.size(); ++l) {
                            row.push_back(delta[k] * input[l]);
                        }
                        weight_deltas.elements.push_back(row);
                    }
                    weights[j] = weights[j] - weight_deltas * learning_rate;
                    biases[j] = biases[j] - delta * learning_rate;
                    error = weights[j].transpose() * delta;
                }
            }
            cout << "Epoch " << epoch + 1 << "/" << epochs << ", Loss: " << total_loss / X.size() << endl;
        }
    };
};
