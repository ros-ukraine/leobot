var delta = 0;
// Connection to ROS
var ros = new ROSLIB.Ros({
    url : 'ws://' + window.location.hostname + ':9090'
});
ros.on('connection', function() {
    console.log('Connected to websocket server.');
});
ros.on('error', function(error) {
    console.log('Error connecting to websocket server: ', error);
});
ros.on('close', function() {
    console.log('Connection to websocket server closed.');
});
var headControl = new ROSLIB.Topic({
    ros : ros,
    name : '/leobot/head_position_controller/command',
    messageType : 'std_msgs/Float64'
});
var listener = new ROSLIB.Topic({
    ros : ros,
    name : '/leobot/head_position_controller/state',
    messageType : 'control_msgs/JointControllerState'
});
listener.subscribe(function(message) {
    delta = message.process_value * 180 / Math.PI;
});
var publishHeadPosition = function() {
        var delta_radians =  delta / 180.0 * Math.PI;
        console.log('degrees = ' + delta + ' radians = ' + delta_radians);
        var positionMess = new ROSLIB.Message({
            data : delta_radians
        });
        headControl.publish(positionMess);
}
document.getElementById('head-control-button-left').onclick = function() {
     delta = (delta > 85) ? 90 : delta + 5;
     publishHeadPosition()
};
document.getElementById('head-control-button-center').onclick = function() {
     delta = 0;
     publishHeadPosition()
};
document.getElementById('head-control-button-right').onclick = function() {
     delta = (delta < -85) ? -90 : delta - 5;
     publishHeadPosition()
};

var siteRoot = window.location.protocol + '//' + window.location.hostname + ':8090' + '/';
document.getElementsByClassName('video-streaming')[0].src = siteRoot + 'stream?topic=/leobot/stereocamera/left/image_raw&width=640&height=470';