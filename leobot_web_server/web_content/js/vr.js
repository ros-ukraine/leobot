var frameHeight = window.innerHeight;
var frameWidth = window.innerWidth;
var frameWidthHalf = Math.round(frameWidth/2);
var siteRoot = location.protocol + '//' + location.hostname + ':8090' + '/';

document.getElementById('right_iframe').src = siteRoot + "stream?topic=/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
document.getElementById('left_iframe').src = siteRoot + "stream?topic=/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;

var alpha, beta, gamma;
// setup event handler to capture the orientation event and store the most recent data in
if (window.DeviceOrientationEvent) {
    // Listen for the deviceorientation event and handle the
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
    name : '/head_position_controller/command',
    messageType : 'std_msgs/Float64'
});
var wheelControl = new ROSLIB.Topic({
    ros : ros,
    name : '/wheel_diff_drive_controller/cmd_vel',
    messageType : 'geometry_msgs/Twist'
});
document.body.addEventListener('keydown', function(e) {
	        if(e.keyCode == "177"){
	            var twistMessageUp = new ROSLIB.Message({
                    linear: { x:  1, y: 0, z: 0 }
                });
                wheelControl.publish(twistMessageUp);
	        }else if(e.keyCode == "176"){
	            var twistMessageDown = new ROSLIB.Message({
                    linear: { x: -1, y: 0, z: 0 }
                });
                wheelControl.publish(twistMessageDown);
	        }else if(e.keyCode == "227"){
	            var twistMessageLeft = new ROSLIB.Message({
                    angular: { x:  0, y: 0, z: 0.1 }
                });
                wheelControl.publish(twistMessageLeft);
	        }else if(e.keyCode == "228"){
	            var twistMessageRight = new ROSLIB.Message({
                    angular: { x:  0, y: 0, z: -0.1 }
                });
                wheelControl.publish(twistMessageRight);
	        }
});
function imusetorientation() {
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
    imusetorientation();
}, 500);