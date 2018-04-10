var headDelta = 0;

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

function publishMessageOnClick(selector, message, topic) {
    $(selector).click(function() {
        publishMessage(message, topic);
    });
}

function publishHeadPosition() {
    var delta_radians = headDelta / 180.0 * Math.PI;
    console.debug('degrees = ' + headDelta + ' radians = ' + delta_radians);
    publishMessage({data: delta_radians}, headControlTopic);
}

function initVideoStreaming(){
    var siteRoot = location.protocol + '//' + location.hostname + ':8090' + '/';
    document.getElementsByClassName('video-streaming')[0].src = siteRoot + 'stream?topic=/stereocamera/left/image_raw&width=640&height=470';
}

function initWheelsOperation() {
    var forwardMessage  = {  linear: { x:  1, y: 0, z: 0 } };
    var leftMessage     = { angular: { x:  0, y: 0, z: 0.1 } };
    var rightMessage    = { angular: { x:  0, y: 0, z: -0.1 } };
    var backwardMessage = {  linear: { x: -1, y: 0, z: 0 } };

    publishMessageOnClick('.button-forward',  forwardMessage,  wheelsTopic);
    publishMessageOnClick('.button-left',     leftMessage,     wheelsTopic);
    publishMessageOnClick('.button-right',    rightMessage,    wheelsTopic);
    publishMessageOnClick('.button-backward', backwardMessage, wheelsTopic);

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
}

function initHeadOperation() {
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
}

function initMap() {
    // Create the main viewer.
    var viewer = new ROS2D.Viewer({
        divID : 'map-tracking',
        width : 400,
        height : 400
    });

    // Setup the map client.
    var gridClient = new NAV2D.OccupancyGridClientNav({
        ros : ros,
        rootObject : viewer.scene,
        // Use this property in case of continuous updates
        continuous: true
    });
}

// Connection to ROS
var ros = new ROSLIB.Ros({
    url : 'ws://' + location.hostname + ':9090'
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

var wheelsTopic       = createTopic('/wheel_diff_drive_controller/cmd_vel', 'geometry_msgs/Twist');
var headControlTopic  = createTopic('/head_position_controller/command', 'std_msgs/Float64');
var headListenerTopic = createTopic('/head_position_controller/state', 'control_msgs/JointControllerState');

wheelsTopic.subscribe(function(message) {
    console.debug('Received message on ' + wheelsTopic.name + ': ', message);
});
headListenerTopic.subscribe(function(message) {
    headDelta = message.process_value * 180 / Math.PI;
});

$(function(event) {
    //initVideoStreaming();
    //initWheelsOperation();
    //initHeadOperation();
    initMap();
});
