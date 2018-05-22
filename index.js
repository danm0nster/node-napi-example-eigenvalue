const ComputeRanks = require("./lib/binding.js");
const groupSize = 5;
const nativeRanks = new ComputeRanks(groupSize);
const attackNumber = 100;
// Simulate 10 attacks
for (let outer = 0; outer < 10; outer++) {
  for (let n = 0; n < attackNumber; n++) {
    const i = Math.floor(Math.random() * groupSize);
    const j = Math.floor(Math.random() * groupSize);
    if (i != j) {
      // console.log("(i,j) = ", i, j);
      nativeRanks.updateAggressionMatrix(i, j);
    }
  }
  nativeRanks.computePowerScores(console.log);
}
nativeRanks.updateAggressionMatrix(1, 2);

// nativeRanks.updateAggressionMatrix(i,j)
// nativeRanks.computePowerScores()

// TODO: create a buffer of incoming attacks and update aggression matrix with several if computePowerScores is still running (set a flag)
const instance = new ComputeRanks(4);
// TODO: Build attacks from an aggression matrix (easier to write)
const attackList = [
  [0, 1], [0, 2], [0, 2], [0, 3], [0, 3], [0, 3],
  [1, 0], [1, 2], [1, 3],
  [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0], [2, 0],
  [2, 1], [2, 1], [2, 1], [2, 3], [2, 3],
  [3, 0], [3, 0], [3, 0], [3, 0], [3, 0], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1]
];
attackList.forEach(function (item, index) {instance.updateAggressionMatrix(item[0], item[1])});
// instance.computePowerScores(console.log)
let solution;
function saveSolution (error, result) {
  console.log("Solution: ", result)
  solution = result;
}
instance.computePowerScores(saveSolution)
