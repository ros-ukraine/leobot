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
    console.debug('Received message on ' + topic.name + ': ', message);
});

document.addEventListener('DOMContentLoaded', function(event) {
    function publishMessage(message) {
        var positionMessage = new ROSLIB.Message(message);
        topic.publish(positionMessage);
    }

    function publishMessageOnClick(elementsClass, message) {
        var elements = document.getElementsByClassName(elementsClass);

        for (var i=0; i<elements.length; i++) {
            elements[i].onclick = function() {
                publishMessage(message);
            };
        }
    }

    var forwardMessage  = {  linear: { x:  1, y: 0, z:   0 } };
    var leftMessage     = { angular: { x:  0, y: 0, z: -15 } };
    var rightMessage    = { angular: { x:  0, y: 0, z:  15 } };
    var backwardMessage = {  linear: { x: -1, y: 0, z:   0 } };

    publishMessageOnClick('button-forward',  forwardMessage);
    publishMessageOnClick('button-left',     leftMessage);
    publishMessageOnClick('button-right',    rightMessage);
    publishMessageOnClick('button-backward', backwardMessage);

    window.addEventListener('keydown', function(e) {
        switch(e.key){
            case 'ArrowUp':
                publishMessage(forwardMessage);
                e.preventDefault();
                break;
            case 'ArrowLeft':
                publishMessage(leftMessage);
                e.preventDefault();
                break;
            case 'ArrowRight':
                publishMessage(rightMessage);
                e.preventDefault();
                break;
            case 'ArrowDown':
                publishMessage(backwardMessage);
                e.preventDefault();
                break;
        }
    });
});
