autowatch = 1;

inlets = 6;
outlets = 2;

setinletassist(0, "bang: trigger wave");
setinletassist(1, "float: amplitude (0.0 to 1.0)");
setinletassist(2, "int: frequency (Hz)");
setinletassist(3, "float: duration (seconds)");
setinletassist(4, "bang: reset to 0, 0");
setinletassist(5, "float: damping constant (>= 0)");

setoutletassist(0, "float: x coordinate (0 to 1)");
setoutletassist(1, "float: y coordinate (damped sine)");

var amplitude = 1.0;
var frequency = 1;
var duration = 1.0;
var damping = 0.0;

var updateRate = 60; // updates per second
var task = new Task(update, this);
task.interval = 1000 / updateRate;

var startTime = 0;
var waveActive = false;
var bangQueued = false;
var lastY = 0;

function bang() {
    if (inlet === 0) {
        if (!waveActive) {
            startWave();
        } else {
            bangQueued = true;
            post("Bang queued – waiting for zero crossing\n");
        }
    } else if (inlet === 4) {
        if (task.running) task.cancel();
        outlet(0, 0.0);
        outlet(1, 0.0);
        waveActive = false;
        bangQueued = false;
    }
}

function startWave() {
    startTime = Date.now();
    waveActive = true;
    task.repeat();
}

function update() {
    var now = Date.now();
    var elapsed = (now - startTime) / 1000.0;

    if (elapsed >= duration) {
        // Even if duration ends, let y go to 0 before stopping
        if (Math.abs(lastY) < 0.0001) {
            task.cancel();
            waveActive = false;

            if (bangQueued) {
                bangQueued = false;
                startWave();
            }
            return;
        }
    }

    // Calculate normalized x
    var x = elapsed / duration;
    var cycles = frequency * elapsed;

    // Custom damping envelope
    var envelope;
    if (cycles < 0.5) {
        envelope = 1.0;
	} else if (cycles < 1) {
		envelope = Math.exp(-damping);
    } else if (cycles < 2) {
        envelope = Math.exp(-damping * 2);
    } else if (cycles < 3) {
        envelope = Math.exp(-damping * 4);
    } else if (cycles < 10) {
        envelope = Math.exp(-damping * 8);
    } else {
        envelope = 0;
    }

    var y = amplitude * envelope * Math.sin(2 * Math.PI * frequency * elapsed);

    outlet(0, x);
    outlet(1, y);

    // Detect zero-crossing for queued bang
    if (bangQueued && ((lastY > 0 && y <= 0) || (lastY < 0 && y >= 0))) {
        task.cancel();
        waveActive = false;
        bangQueued = false;
        startWave();
        return; // Skip the rest of the update until new wave starts
    }

    lastY = y;
}

function msg_int(value) {
    if (inlet === 2) {
        frequency = value;
    }
}

function msg_float(value) {
    switch (inlet) {
        case 1:
            amplitude = value;
            break;
        case 3:
            duration = value;
            break;
        case 5:
            damping = Math.max(0.0, value);
            break;
    }
}

