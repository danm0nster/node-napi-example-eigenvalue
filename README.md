# node-napi-example-eigenvalue
Example of node.js app calling native C++ code doing linear algebra with Eigen

You need a recent version of node.js supporting the N-API interface for native modules. You also need node-gyp and Eigen installed.

To install, build and run the code you should roughly do the following:
1. `git clone https://github.com/danm0nster/node-napi-example-eigenvalue.git napi-example`
1. `cd napi-example`
1. `npm install`
1. `node test/test_binding.js`

## Installing required software
1. Node.js can be downloaded from the [official site](https://nodejs.org/en/)
1. Install the node.js native add-on build tool node-gyp with npm: `$ npm install -g node-gyp`
1. Install [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) from source or by using package, e.g.
    * Mac OS (using [brew](https://brew.sh)): `$ brew install eigen`
    * Linux (Debian | Ubuntu): `$ apt-get install libeigen3-dev`
