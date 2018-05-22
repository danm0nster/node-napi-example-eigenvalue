const addon = require('../build/Release/compute-ranks-native');

function ComputeRanks(dimension) {
    this.computePowerScores = function(str) {
        return _addonInstance.computePowerScores(str);
    }
    this.updateAggressionMatrix = function(i, j) {
        return _addonInstance.updateAggressionMatrix(i, j);
    }
    var _addonInstance = new addon.ComputeRanks(dimension);
}

module.exports = ComputeRanks;
