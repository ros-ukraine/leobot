var frameHeight = window.innerHeight;
var frameWidth = window.innerWidth;
var frameWidthHalf = Math.round(frameWidth/2);
document.getElementById('right_iframe').src = "http://0.0.0.0:8090/stream?topic=/leobot/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
document.getElementById('left_iframe').src = "http://0.0.0.0:8090/stream?topic=/leobot/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;

// setup event handler to capture the orientation event and store the most recent data in a variable


// Connecting to ROS
var ros = new ROSLIB.Ros({
    url : 'ws://localhost:9090'
});
ros.on('connection', function() {
    console.log('Connected to websocket server.');

    var alpha;

    if (window.DeviceOrientationEvent) {
        // Listen for the deviceorientation event and handle the raw data
        window.addEventListener('deviceorientation', function(eventData) {

            // alpha is the compass direction the device is facing in degrees
            alpha = eventData.alpha
            console.log(alpha);
        }, false);
    };

    var headControl = new ROSLIB.Topic({
        ros : ros,
        name : '/leobot/head_position_controller/command',
        messageType : 'std_msgs/Float64'
    });

    var alpha_radian = ((alpha + 360) / 360 * 2 * Math.PI) % (2 * Math.PI);
    console.log(alpha_radian);
    
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

