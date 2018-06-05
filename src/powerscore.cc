#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include "powerscore.h"

void PowerScoreWorker::ComputeEigenValueCentrality(Eigen::MatrixXd A, Eigen::RowVectorXd &powerScores) {
  int dimension = A.rows();
  int idxMax;
  float epsilon = 1e-6;
  Eigen::MatrixXd T(dimension, dimension);
  Eigen::MatrixXd I(dimension, dimension);
  Eigen::MatrixXd Ones(dimension, dimension);
  Eigen::MatrixXd denominator(dimension, dimension);
  Eigen::VectorXd rowSum(dimension);
  I = Eigen::MatrixXd::Identity(dimension, dimension);
  Ones = Eigen::MatrixXd::Zero(dimension, dimension);
  Ones.setOnes(dimension, dimension);
  denominator = Eigen::MatrixXd::Zero(dimension, dimension);
  powerScores = Eigen::RowVectorXd(dimension);
  // Compute the transition matrix T from the aggression matrix A
  // Start constructing T by adding eps to non-diagonal elements of A
  T = A + epsilon * (Ones - I);
  // Compute row sums for normalization to conditional probabilities
  rowSum = T.rowwise().sum();
  denominator = rowSum.replicate(1, dimension);
  // Perform element wise division to get the transition matrix
  T = T.array() / denominator.array();
  // Compute eigenvalues and eigenvectors of the transpose of T (to get left hand eigenvalues)
  Eigen::EigenSolver<Eigen::MatrixXd> es(T.transpose());
  // Find the eigenvalue with the largest absolute value
  es.eigenvalues().array().abs().maxCoeff(&idxMax);
  // Pick the corresponding eigenvector, and compute power score
  powerScores = es.eigenvectors().transpose().row(idxMax).array().abs();
}
