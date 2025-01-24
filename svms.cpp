#include "backbone.cpp"
#include <vector>
#include <iostream>

class SVM {
public:
    SVM(double C, double tol, double max_passes) : C(C), tol(tol), max_passes(max_passes) {}

    void fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
        gradientDescent(X, y);
    }

private:
    double C;
    double tol;
    double max_passes;
};

int main() {
    // Example usage of the SVM class
    std::vector<std::vector<double>> X = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0}};
    std::vector<int> y = {1, -1, 1};

    SVM svm(1.0, 0.001, 10);
    svm.fit(X, y);

    std::vector<double> x = {2.0, 3.0};
    int prediction = svm.predict(x);
    std::cout << "Prediction: " << prediction << std::endl;

    return 0;
}
void SVM::fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
    int m = X.size();
    int n = X[0].size();
    std::vector<double> alphas(m, 0);
    double b = 0;
    int passes = 0;

    while (passes < max_passes) {
        int num_changed_alphas = 0;
        for (int i = 0; i < m; ++i) {
            double Ei = b;
            for (int k = 0; k < n; ++k) {
                Ei += alphas[k] *