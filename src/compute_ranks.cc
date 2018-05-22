#include "compute_ranks.h"
#include "powerscore.h"
#include <cmath>
#include <Eigen/Dense>

// This initializes an instance of the class
ComputeRanks::ComputeRanks(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    // Validate input
    if (info.Length() < 1) {
        Napi::TypeError::New(env, "ComputeRanks must be initialized with 1 argument")
          .ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Dimension must be a number")
          .ThrowAsJavaScriptException();
        return;
    }
    // Test if the argument is an integer
    if (std::trunc(info[0].As<Napi::Number>().DoubleValue()) != info[0].As<Napi::Number>().DoubleValue()) {
      Napi::TypeError::New(env, "Please specify an integer dimension")
        .ThrowAsJavaScriptException();
      return;
    }
    this->_dimension = info[0].As<Napi::Number>().DoubleValue();
    this->_A = Eigen::MatrixXd::Zero(this->_dimension, this->_dimension);
}

Napi::Value ComputeRanks::ComputePowerScores(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments")
          .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsFunction()) {
        Napi::TypeError::New(env, "Callback must be a JavaScript function")
          .ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Function callback = info[0].As<Napi::Function>();

    PowerScoreWorker* worker = new PowerScoreWorker(callback, this->_A);
    worker->Queue();
    // Return immediately, while the work is being done asynchonously
    return info.Env().Undefined();
}

Napi::Value ComputeRanks::UpdateAggressionMatrix(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    // Check that there are exactly 2 arguments
    if (info.Length() != 2) {
        Napi::TypeError::New(env, "UpdateAggressionMatrix needs 2 arguments")
          .ThrowAsJavaScriptException();
        return env.Null();
    }
    // Check that arguments are numbers
    if (!info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Arguments to UpdateAggressionMatrix must be numbers")
          .ThrowAsJavaScriptException();
        return env.Null();
    }
    // Check that arguments are integers
    if ( (std::trunc(info[0].As<Napi::Number>().DoubleValue()) != info[0].As<Napi::Number>().DoubleValue()) ||
         (std::trunc(info[1].As<Napi::Number>().DoubleValue()) != info[1].As<Napi::Number>().DoubleValue()) ) {
      Napi::TypeError::New(env, "Arguments to UpdateAggressionMatrix must be integers")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    int i = info[0].As<Napi::Number>().Int32Value();
    int j = info[1].As<Napi::Number>().Int32Value();
    // Check that arguments are within expected limits 0 <= i,j < this->_dimension and not equal
    if (i < 0 || j < 0) {
      Napi::TypeError::New(env, "Arguments to UpdateAggressionMatrix must be non-negative")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (i >= this->_dimension || j >= this->_dimension) {
      Napi::TypeError::New(env, "Arguments to UpdateAggressionMatrix must be less than the dimension of the aggression matrix")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (i == j) {
      Napi::TypeError::New(env, "Arguments to UpdateAggressionMatrix must not be identical (no self-aggression)")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    // Add the attack to aggression matrix
    this->_A(i, j) += 1;
    return env.Null();
}

// Define the methods that can be called from JavaScript
Napi::Function ComputeRanks::GetClass(Napi::Env env) {
    return DefineClass(env, "ComputeRanks", {
        ComputeRanks::InstanceMethod("computePowerScores", &ComputeRanks::ComputePowerScores),
        ComputeRanks::InstanceMethod("updateAggressionMatrix", &ComputeRanks::UpdateAggressionMatrix),
    });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "ComputeRanks");
    exports.Set(name, ComputeRanks::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)
