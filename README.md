# node-napi-example-eigenvalue
Example of node.js app calling native C++ code doing linear algebra with Eigen

You need a recent version of node.js supporting the N-API interface for native modules. You also need node-gyp and Eigen installed.

To install, build and run the code you should roughly do the following:
1. `git clone https://github.com/danm0nster/node-napi-example-eigenvalue.git napi-example`
1. `cd napi-example`
1. `npm install`
1. `node test/test_binding.js`

## Issues
It seems the `'conditions'` part of `binding.gyp` is ignored, so to build for a particular platform you need to copy parts to the `'targets'` section.
