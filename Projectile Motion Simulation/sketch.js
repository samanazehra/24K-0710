let velocityslider, angleslider; 
let points = [];                 
let running = true;

function setup() {
    createCanvas(1230, 510);
    velocityslider = createSlider(10, 100, 50, 1);
    velocityslider.position(20, 115);
    angleslider = createSlider(0, 90, 45, 1);
    angleslider.position(20, 145);
}  

function draw() {
    background(220);
    drawgrid();
    displaystats();
    if (running) {
        let velocity = velocityslider.value();
        let angle = radians(angleslider.value());
        let gravity = 9.81;
        let time = frameCount / 60;
        let x = velocity * cos(angle) * time;
        let y = velocity * sin(angle) * time - 0.5 * gravity * time * time;
        if (y >= 0) {
            points.push({ x: x, y: height - y });
        } else {
            running = false;
        }
        drawtrajectory();
        fill(255, 0, 0);
        ellipse(x, height - y, 10, 10);
        drawshadow(x);
        displaycoordinates(x, height - y);
        drawprojectile(x, height - y);
    }
}

function calculatestats(velocity, angle) {
    let gravity = 9.81;
    let maxheight = (velocity * velocity * sin(angle) * sin(angle)) / (2 * gravity);
    let range = (velocity * velocity * sin(2 * angle)) / gravity;
    let timeofflight = (2 * velocity * sin(angle)) / gravity;
    return { maxheight, range, timeofflight };
}

function displaystats() {
    let velocity = velocityslider.value();
    let angle = radians(angleslider.value());
    let { maxheight, range, timeofflight } = calculatestats(velocity, angle);
    fill(0, 0, 0);
    textSize(16);
    text("slide to adjust velocity", 160, 50);
    text("slide to adjust angle", 160, 80);
    text(`Velocity: ${velocity}m/s`, 20, 140);
    text(`Angle: ${degrees(angle)}°`, 20, 160);
    text(`Maximum height reached by object: ${maxheight.toFixed(2)} meters`, 20, 180);
    text(`Maximum range covered by object: ${range.toFixed(2)} meters`, 20, 200);
    text(`Time of flight: ${timeofflight.toFixed(2)} seconds`, 20, 220);
}

function drawgrid() {
    stroke(200);
    for (let x = 0; x < width; x += 10) {
        line(x, 0, x, height);
    }
    for (let y = 0; y < height; y += 10) {
        line(0, y, width, y);
    }
}

function displaycoordinates(x, y) {
    fill(0);
    textSize(16);
    text(`Current Position: (${x.toFixed(2)} m, ${y.toFixed(2)} m)`, 500, 300);
}

function drawshadow(x) {
    fill(50, 50, 50, 100);
    noStroke();
    ellipse(x, height - 5, 15, 5); 
}

function drawprojectile(x, y) {
    let heightfactor = map(y, 0, height, 255, 0);
    fill(heightfactor, 0, 255 - heightfactor);
    noStroke();
    ellipse(x, y, 10, 10);
}

function drawtrajectory() {
    stroke(0); 
    noFill(); 
    beginShape();
    for (let p of points) {
        vertex(p.x, p.y);
    }
    endShape();
}

function keyPressed() {
    if (key === 'P' || key === 'p') {
        running = !running;
    }
    if (key === 'R' || key === 'r') {
        frameCount = 0;
        points = []; 
        running = true; 
    }
}
