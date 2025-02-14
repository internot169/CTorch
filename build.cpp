#include "src/models/linearpredictor.cpp"
#include "src/models/neuralnetwork.cpp"
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/function.h>
using namespace std;

NB_MODULE(toyml, m) {
    nb::class_<LinearPredictor>(m, "LinearPredictor")
        .constructor([](vector<double> weights, double bias) {
            return new LinearPredictor(Vector(weights), bias);
        })
        .method("predict", &LinearPredictor::predict)
        .method("fit", &LinearPredictor::fit);
    nb::class_<NeuralNetwork>(m, "NeuralNetwork")
        .constructor([](vector<Matrix> weights, vector<Vector> biases, vector<function<double(double)>> activations) {
            return new NeuralNetwork(weights, biases, activations);
        })
        .method("predict", &NeuralNetwork::predict)
        .method("fit", &NeuralNetwork::fit);
}