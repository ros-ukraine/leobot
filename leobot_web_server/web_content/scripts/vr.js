var frameHeight = window.innerHeight;
var frameWidth = window.innerWidth;
var frameWidthHalf = Math.round(frameWidth/2);
document.getElementById('right_iframe').src = window.location.protocol + '//' + window.location.hostname + ":8090/stream?topic=/leobot/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
document.getElementById('left_iframe').src = window.location.protocol + '//' + window.location.hostname + ":8090/stream?topic=/leobot/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
var alpha, beta, gamma;
// setup event handler to capture the orientation event and store the most recent data in a variable
if (window.DeviceOrientationEvent) {
    // Listen for the deviceorientation event and handle the raw data
    window.addEventListener('deviceorientation', function(eventData) {
        gamma = eventData.gamma;
        alpha = eventData.alpha
    }, false);
};
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
function imusnapshot() {
    if(((alpha > 0 && alpha < 90) && (gamma >= (-90) && gamma <= 0))
    || ((alpha > 270 && alpha < 360) && (gamma >= (-90) && gamma <= 0))
    || ((gamma > 0 && gamma <= 90) && (alpha > 180 && alpha < 270))
    || ((gamma > 0 && gamma <= 90) && (alpha > 90 && alpha < 180)))
    {
         if ((alpha > 0 && alpha < 90) && (gamma >= (-90) && gamma <= 0 )) {
              alpha = alpha;
         }else if ((alpha > 270 && alpha < 360) && (gamma >= (-90) && gamma <= 0)){
              alpha = alpha - 360;
         }else if ((gamma > 0 && gamma <= 90) && (alpha > 180 && alpha < 270)){
              alpha = alpha - 180;
         }else if ((gamma > 0 && gamma <= 90) && (alpha > 90 && alpha < 180)){
              alpha = alpha + 180 - 360;
         }
         var alpha_radian = alpha / 180.0 * Math.PI;
         var imuMessage = new ROSLIB.Message({
            data : alpha_radian
         });
         headControl.publish(imuMessage);
    }
}
setInterval(function(){
    imusnapshot();
}, 500);