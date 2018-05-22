const ComputeRanks = require("../lib/binding.js");
const assert = require("assert");

assert(ComputeRanks, "The expected module is undefined");

function testBasic()
{
    const instance = new ComputeRanks(4);
    const attackList = [
      [0, 1], [0, 2], [0, 2], [0, 3], [0, 3], [0, 3],
      [1, 0], [1, 2], [1, 3],
      [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0],
      [2, 1], [2, 1], [2, 1], [2, 3], [2, 3],
      [3, 0], [3, 0], [3, 0], [3, 0], [3, 0], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1]
    ];
    attackList.forEach(function (item, index) {instance.updateAggressionMatrix(item[0], item[1])});
    const reference = [0.6434, 0.4369, 0.3601, 0.5153];
    // conputePowerScores is an async function, so provide test as callback function.
    function checkSolution (error, result) {
      result.forEach(function (item, index) {result[index] = round(item, 4)})
      result.forEach(function (item, index) {assert.equal(item, reference[index])})
    }
    instance.computePowerScores(checkSolution)
}

function testInvalidParams()
{
    const instance = new ComputeRanks();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed --- everything looks OK!");

// Precision rounding without errors
// http://www.jacklmoore.com/notes/rounding-in-javascript/
function round(value, decimals) {
  return Number(Math.round(value+'e'+decimals)+'e-'+decimals);
}
