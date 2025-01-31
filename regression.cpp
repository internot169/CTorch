#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/function.h>
#include <./backbone.cpp>

class LinearRegression {
public:
    LinearRegression() : slope(0), intercept(0) {}

    void fit(const vector<double>& x, const vector<double>& y) {
        int n = x.size();
        double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

        for (int i = 0; i < n; ++i) {
            sum_x += x[i];
            sum_y += y[i];
            sum_xy += x[i] * y[i];
            sum_xx += x[i] * x[i];
        }

        slope = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
        intercept = (sum_y - slope * sum_x) / n;
    }

    double predict(double x) const {
        return slope * x + intercept;
    }

    vector<double> predict(const vector<double>& x) const {
        vector<double> predictions;
        for (double xi : x) {
            predictions.push_back(predict(xi));
        }
        return predictions;
    }

private:
    double slope;
    double intercept;
};

NB_MODULE(regression, m) {
    nanobind::class_<LinearRegression>(m, "LinearRegression")
        .def(nanobind::init<>())
        .def("fit", &LinearRegression::fit)
        .def("predict", nanobind::overload_cast<double>(&LinearRegression::predict, nanobind::const_))
        .def("predict", nanobind::overload_cast<const vector<double>&>(&LinearRegression::predict, nanobind::const_));
}