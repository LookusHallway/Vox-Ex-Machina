autowatch = 1;

inlets = 2;
outlets = 1;

setinletassist(0, "float: pitch input (50 to 500)");
setinletassist(1, "int: number of thresholds");

setoutletassist(0, "bang: when new threshold is crossed");

var minPitch = 50;
var maxPitch = 500;
var numThresholds = 1;
var lastZone = -1;

function msg_float(value) {
    if (inlet === 0) {
        var pitch = Math.max(minPitch, Math.min(maxPitch, value));
        var zone = getZone(pitch);
        
        if (zone !== lastZone) {
            outlet(0, "bang");
            lastZone = zone;
        }
    }
}

function msg_int(value) {
    if (inlet === 1) {
        numThresholds = Math.max(1, value);
        lastZone = -1; // reset zone on threshold count change
    }
}

function getZone(pitch) {
    var range = maxPitch - minPitch;
    var zoneSize = range / numThresholds;
    var zone = Math.floor((pitch - minPitch) / zoneSize);
    
    // Clamp to avoid overflow on upper edge
    if (zone >= numThresholds) {
        zone = numThresholds - 1;
    }
    return zone;
}
