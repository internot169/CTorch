#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <nanobind/nanobind.h>

namespace nb = nanobind;
using namespace Eigen;

class PCA {
public:
    PCA(int n_components) : n_components(n_components) {}

    void fit(const MatrixXd& X) {
        // Center the data
        MatrixXd X_centered = X.rowwise() - X.colwise().mean();

        // Compute covariance matrix
        MatrixXd covariance_matrix = (X_centered.adjoint() * X_centered) / double(X.rows() - 1);

        // Compute eigenvalues and eigenvectors
        SelfAdjointEigenSolver<MatrixXd> eigen_solver(covariance_matrix);
        eigenvalues = eigen_solver.eigenvalues().reverse();
        eigenvectors = eigen_solver.eigenvectors().rowwise().reverse();

        // Select the top n_components
        eigenvectors = eigenvectors.leftCols(n_components);
    }

    MatrixXd transform(const MatrixXd& X) {
        MatrixXd X_centered = X.rowwise() - X.colwise().mean();
        return X_centered * eigenvectors;
    }

    VectorXd get_eigenvalues() const {
        return eigenvalues.head(n_components);
    }

private:
    int n_components;
    MatrixXd eigenvectors;
    VectorXd eigenvalues;
};

NB_MODULE(pca_module, m) {
    nb::class_<PCA>(m, "PCA")
        .def(nb::init<int>())
        .def("fit", &PCA::fit)
        .def("transform", &PCA::transform)
        .def("get_eigenvalues", &PCA::get_eigenvalues);
}