#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <string>
using namespace std;
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/function.h>

using Vector = vector<double>;
using Matrix = vector<Vector>;
using VectorFunction = function<double(Vector)>;

// When working with neural networks (Week 6), this needs to generalize to other dimensions - use a Jacobian Matrix
// Potentially (if time at the END of the study) - this could use calculus instead of numerical methods
// Note that each parameter depends on the gradient of the loss of the function with respect to the whole dataset
Vector gradient(Vector params, VectorFunction f, double numericalStep = 0.001) {
    Vector grad;
    for (int i = 0; i < params.size(); ++i) {
        Vector inputPlus = params;
        inputPlus[i] += numericalStep;
        Vector inputMinus = params;
        inputMinus[i] -= numericalStep;
        grad.push_back((f(inputPlus) - f(inputMinus)) / (2 * numericalStep));
    }
    return grad;
}

// When doing neural networks, this would need to do two things:
// change to be our loss function - the loss of the network with a certain set of parameters over our dataset
// Allow us to manipulate the subsets of the dataset for stochastic gradient descent
double testFunction(Vector input) 
{ 
    return (0.5 * ((input[0] * ((2 * input[0]) + input[1])) + (input[1] * (input[0] + (20 * input[1]))))) - (5 * input[0]) + (3 * input[1]); 
}

/* Note: neural networks are not the only thing that would generalize for above. Other patterns should work - make this extensible*/
/* A_i */
// https://cs231n.github.io/optimization-1/
// Some theorems: https://web.stanford.edu/class/cs224n/readings/gradient-notes.pdf
/// Analytic gradients may be a bit too difficult for this project, but it would be a good idea to look into them
/// But, this idea also makes it trivial: https://karpathy.github.io/neuralnets/
// https://www.youtube.com/watch?v=JLEeKnhUuUM

string printVector(Vector input) {
    string result = "";

    for (size_t i = 0; i < input.size(); ++i) {
        result += to_string(input[i]);
        if (i != input.size() - 1) {
            result += ", ";
        }
    }

    return result;
}

Vector gradientDescent(VectorFunction f, Vector params, Vector paramsPrev, double learningRate = 0.01, double alpha = 0.9) {
    Vector grad = gradient(params, f);
    for (int j = 0; j < params.size(); ++j) {
        params[j] -= learningRate * grad[j] + alpha * (params[j] - paramsPrev[j]);
    }
    return params;
}

NB_MODULE(optimization, m) {
    m.def("gradient", &gradient, "A function to calculate the gradient of a function");
    m.def("testFunction", &testFunction, "A test function for optimization");
    m.def("gradientDescent", &gradientDescent, "A function to perform gradient descent");
    m.def("printVector", &printVector, "A function to print a vector");
}