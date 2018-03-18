var headDelta = 0;

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

function createTopic(name, type) {
    return new ROSLIB.Topic({
        ros: ros,
        name: name,
        messageType: type
    });
}

function publishMessage(message, topic) {
    topic.publish(new ROSLIB.Message(message));
}

function publishMessageOnClick(elementsClass, message, topic) {
    var elements = document.getElementsByClassName(elementsClass);

    for (var i=0; i<elements.length; i++) {
        elements[i].onclick = function() {
            publishMessage(message, topic);
        };
    }
}

function publishHeadPosition() {
    var delta_radians =  headDelta / 180.0 * Math.PI;
    console.log('degrees = ' + headDelta + ' radians = ' + delta_radians);
    publishMessage({data: delta_radians}, headControlTopic);
}

var wheelsTopic       = createTopic('/leobot/wheel_diff_drive_controller/cmd_vel', 'geometry_msgs/Twist');
var headControlTopic  = createTopic('/leobot/head_position_controller/command', 'std_msgs/Float64');
var headListenerTopic = createTopic('/leobot/head_position_controller/state', 'control_msgs/JointControllerState');

wheelsTopic.subscribe(function(message) {
    console.debug('Received message on ' + wheelsTopic.name + ': ', message);
});
headListenerTopic.subscribe(function(message) {
    headDelta = message.process_value * 180 / Math.PI;
});

document.addEventListener('DOMContentLoaded', function(event) {
    var siteRoot = window.location.protocol + '//' + window.location.hostname + ':8090' + '/';
    document.getElementsByClassName('video-streaming')[0].src = siteRoot + 'stream?topic=/leobot/stereocamera/left/image_raw&width=640&height=470';

    var forwardMessage  = {  linear: { x:  1, y: 0, z:   0 } };
    var leftMessage     = { angular: { x:  0, y: 0, z: -15 } };
    var rightMessage    = { angular: { x:  0, y: 0, z:  15 } };
    var backwardMessage = {  linear: { x: -1, y: 0, z:   0 } };

    publishMessageOnClick('button-forward',  forwardMessage,  wheelsTopic);
    publishMessageOnClick('button-left',     leftMessage,     wheelsTopic);
    publishMessageOnClick('button-right',    rightMessage,    wheelsTopic);
    publishMessageOnClick('button-backward', backwardMessage, wheelsTopic);

    window.addEventListener('keydown', function(e) {
        switch(e.key){
            case 'ArrowUp':
                publishMessage(forwardMessage, wheelsTopic);
                e.preventDefault();
                break;
            case 'ArrowLeft':
                publishMessage(leftMessage, wheelsTopic);
                e.preventDefault();
                break;
            case 'ArrowRight':
                publishMessage(rightMessage, wheelsTopic);
                e.preventDefault();
                break;
            case 'ArrowDown':
                publishMessage(backwardMessage, wheelsTopic);
                e.preventDefault();
                break;
        }
    });

    document.getElementById('head-control-button-left').onclick = function() {
         headDelta = (headDelta > 85) ? 90 : headDelta + 5;
         publishHeadPosition()
    };
    document.getElementById('head-control-button-center').onclick = function() {
         headDelta = 0;
         publishHeadPosition()
    };
    document.getElementById('head-control-button-right').onclick = function() {
         headDelta = (headDelta < -85) ? -90 : headDelta - 5;
         publishHeadPosition()
    };
});
