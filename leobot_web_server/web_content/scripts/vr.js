var frameHeight = window.innerHeight;
var frameWidth = window.innerWidth;
var frameWidthHalf = Math.round(frameWidth/2);
document.getElementById('right_iframe').src = "http://192.168.1.107:8090/stream?topic=/leobot/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
document.getElementById('left_iframe').src = "http://192.168.1.107:8090/stream?topic=/leobot/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;

// setup event handler to capture the orientation event and store the most recent data in a variable
var d = document.getElementById("elem");
d.innerHTML = 0 + " " + 1;
var z;
var y;
var x;
function handleOrientation(event) {
    console.log("hello");
    x = event.beta;  // In degree in the range [-180,180]
    y = event.gamma; // In degree in the range [-90,90]
    z = event.alpha;
    var absolute = event.absolute;
    console.log(x,y,z);


}

window.addEventListener('deviceorientation', handleOrientation);

// Connecting to ROS

var ros = new ROSLIB.Ros({
    url : 'ws://192.168.1.107:9090'
});
ros.on('connection', function() {
    console.log('Connected to websocket server.');





    var headControl = new ROSLIB.Topic({
        ros : ros,
        name : '/leobot/head_position_controller/command',
        messageType : 'std_msgs/Float64'
    });

    var alpha_radian = ((z + 360) / 360 * 2 * Math.PI) % (2 * Math.PI);
    console.log(alpha_radian);
    d.innerHTML = x + ", " + y + ", " + z + ", " + alpha_radian;
    var positionMess = new ROSLIB.Message({
        data : alpha_radian
    });

    headControl.publish(positionMess);
});
ros.on('error', function(error) {
    console.log('Error connecting to websocket server: ', error);
});
ros.on('close', function() {
    console.log('Connection to websocket server closed.');
});