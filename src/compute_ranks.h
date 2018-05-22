#pragma once

#include <napi.h>
#include <Eigen/Dense>

class ComputeRanks : public Napi::ObjectWrap<ComputeRanks> {
public:
    ComputeRanks(const Napi::CallbackInfo&);
    Napi::Value ComputePowerScores(const Napi::CallbackInfo&);
    Napi::Value UpdateAggressionMatrix(const Napi::CallbackInfo&);

    static Napi::Function GetClass(Napi::Env);

private:
    int _dimension;
    Eigen::MatrixXd _A;
};
