#pragma once

#include <napi.h>
#include <Eigen/Dense>

// Define a class for the asynchronous worker to run in separate thread
class PowerScoreWorker : public Napi::AsyncWorker {
public:
  // Matrix as pointer or by value?  Can it be updated while this is running?
  PowerScoreWorker(Napi::Function& callback, Eigen::MatrixXd& AggressionMatrix)
    : Napi::AsyncWorker(callback), AggressionMatrix(AggressionMatrix) {}
    ~PowerScoreWorker() {}

    void Execute() {
      // This is where the heavy work gets done asynchronously. There is no
      // access to the JavaScript environment here.
      ComputeEigenValueCentrality(this->AggressionMatrix, this->PowerScores);
    }

    void OnOK() {
      Napi::HandleScope scope(Env());
      int dimension = AggressionMatrix.rows();
      Napi::Array result = Napi::Array::New(Env(), dimension);
      // Copy power scores to Napi:array result
      for (int i = 0; i < dimension; i++) {
        result[i] = this->PowerScores[i];
      }
      Callback().Call({Env().Undefined(), result});
    }
  void ComputeEigenValueCentrality(Eigen::MatrixXd A, Eigen::RowVectorXd &powerScores);

  private:
    Eigen::RowVectorXd PowerScores;
    Eigen::MatrixXd AggressionMatrix;
};
