#include "backbone.cpp"
#include <vector>
#include <iostream>
#include <cmath>

class SVM {
public:
    SVM(double C, double tol, double max_passes) : C(C), tol(tol), max_passes(max_passes) {}

    void fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y);
    int predict(const std::vector<double>& x);

private:
    double C;
    double tol;
    double max_passes;
    std::vector<double> alphas;
    double b;
    std::vector<std::vector<double>> X;
    std::vector<int> y;

    double kernel(const std::vector<double>& x1, const std::vector<double>& x2);
};

void SVM::fit(const std::vector<std::vector<double>>& X, const std::vector<int>& y) {
    this->X = X;
    this->y = y;
    int m = X.size();
    int n = X[0].size();
    alphas = std::vector<double>(m, 0);
    b = 0;
    int passes = 0;

    while (passes < max_passes) {
        int num_changed_alphas = 0;
        for (int i = 0; i < m; ++i) {
            double Ei = b;
            for (int k = 0; k < m; ++k) {
                Ei += alphas[k] * y[k] * kernel(X[k], X[i]);
            }
            Ei -= y[i];

            if ((y[i] * Ei < -tol && alphas[i] < C) || (y[i] * Ei > tol && alphas[i] > 0)) {
                int j = i;
                while (j == i) {
                    j = rand() % m;
                }

                double Ej = b;
                for (int k = 0; k < m; ++k) {
                    Ej += alphas[k] * y[k] * kernel(X[k], X[j]);
                }
                Ej -= y[j];

                double alpha_i_old = alphas[i];
                double alpha_j_old = alphas[j];

                double L, H;
                if (y[i] != y[j]) {
                    L = std::max(0.0, alphas[j] - alphas[i]);
                    H = std::min(C, C + alphas[j] - alphas[i]);
                } else {
                    L = std::max(0.0, alphas[i] + alphas[j] - C);
                    H = std::min(C, alphas[i] + alphas[j]);
                }

                if (L == H) continue;

                double eta = 2 * kernel(X[i], X[j]) - kernel(X[i], X[i]) - kernel(X[j], X[j]);
                if (eta >= 0) continue;

                alphas[j] -= y[j] * (Ei - Ej) / eta;
                alphas[j] = std::min(H, alphas[j]);
                alphas[j] = std::max(L, alphas[j]);

                if (std::abs(alphas[j] - alpha_j_old) < 1e-5) continue;

                alphas[i] += y[i] * y[j] * (alpha_j_old - alphas[j]);

                double b1 = b - Ei - y[i] * (alphas[i] - alpha_i_old) * kernel(X[i], X[i]) - y[j] * (alphas[j] - alpha_j_old) * kernel(X[i], X[j]);
                double b2 = b - Ej - y[i] * (alphas[i] - alpha_i_old) * kernel(X[i], X[j]) - y[j] * (alphas[j] - alpha_j_old) * kernel(X[j], X[j]);

                if (0 < alphas[i] && alphas[i] < C) {
                    b = b1;
                } else if (0 < alphas[j] && alphas[j] < C) {
                    b = b2;
                } else {
                    b = (b1 + b2) / 2;
                }

                num_changed_alphas++;
            }
        }

        if (num_changed_alphas == 0) {
            passes++;
        } else {
            passes = 0;
        }
    }
}

double SVM::kernel(const std::vector<double>& x1, const std::vector<double>& x2) {
    double result = 0;
    for (size_t i = 0; i < x1.size(); ++i) {
        result += x1[i] * x2[i];
    }
    return result;
}

int SVM::predict(const std::vector<double>& x) {
    double result = b;
    for (size_t i = 0; i < X.size(); ++i) {
        result += alphas[i] * y[i] * kernel(X[i], x);
    }
    return result >= 0 ? 1 : -1;
}
