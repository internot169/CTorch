#include <iostream>
#include <functional>
#include <cmath>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/function.h>
#include "linearpredictor.cpp"
#include "neuralnetwork.cpp"
#include "pca.cpp"
#include "svm.cpp"
using namespace std;

NB_MODULE(toyml, m) {
    nanobind::class_<Vector>(m, "Vector")
        .def(nanobind::init<vector<double>>())
        .def("to_vector", &Vector::to_vector);

    nanobind::class_<Matrix>(m, "Matrix")
        .def(nanobind::init<vector<vector<double>>>());

    nanobind::class_<LinearPredictor>(m, "LinearPredictor")
        .def(nanobind::init<vector<double>, double>())
        .def("predict", &LinearPredictor::predict)
        .def("fit", &LinearPredictor::fit);
    
    nanobind::class_<NeuralNetwork>(m, "NeuralNetwork")
        .def(nanobind::init<vector<Matrix>, vector<Vector>, vector<function<double(double)>>>())
        .def("predict", &NeuralNetwork::predict)
        .def("fit", &NeuralNetwork::fit);
    
    nanobind::class_<PCA>(m, "PCA")
        .def(nanobind::init<int>())
        .def("fit", &PCA::fit)
        .def("transform", &PCA::transform)
        .def("fit_transform", &PCA::fit_transform);

    nanobind::class_<SVM>(m, "SVM")
        .def(nanobind::init<double, double>())
        .def("fit", &SVM::fit)
        .def("predict", &SVM::predict);
}