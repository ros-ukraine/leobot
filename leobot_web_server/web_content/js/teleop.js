var topicName = '/leobot/wheel_diff_drive_controller/cmd_vel';

// Connection to ROS
var ros = new ROSLIB.Ros({
    url : 'ws://' + window.location.hostname + ':9090'
});
ros.on('connection', function() {
    console.log('Connected to websocket server.');
});
ros.on('error', function(error) {
    console.error('Error connecting to websocket server: ', error);
});
ros.on('close', function() {
    console.log('Connection to websocket server closed.');
});

var topic = new ROSLIB.Topic({
    ros : ros,
    name : topicName,
    messageType : 'geometry_msgs/Twist'
});

topic.subscribe(function(message) {
    console.log('Received message on ' + topic.name + ': ', message);
});

document.addEventListener("DOMContentLoaded", function(event) {
    function publishMessageOnClick(elementsClass, message) {
        var elements = document.getElementsByClassName(elementsClass);

        for (var i=0; i<elements.length; i++) {
            elements[i].onclick = function() {
                var positionMessage = new ROSLIB.Message(message);
                topic.publish(positionMessage);
            };
        }
    }

    publishMessageOnClick('button-forward', { linear: { x: 1, y: 0, z: 0 } });
});
