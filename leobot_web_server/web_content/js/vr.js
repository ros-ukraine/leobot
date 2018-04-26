var docelem = document.documentElement;
function fs_status() {
  if (document.fullscreenElement) {
    return 1;
  }
  else if (document.webkitFullscreenElement) {
    return 1;
  }
  else if (document.mozFullScreenElement) {
    return 1;
  }
  else return -1;
}
function setFullScreen() {
  if (docelem.requestFullscreen) {
    docelem.requestFullscreen();
  }
  else if (docelem.mozRequestFullScreen) {
    docelem.mozRequestFullScreen();
  }
  else if (docelem.webkitRequestFullScreen) {
    docelem.webkitRequestFullScreen();
  }
  else if (docelem.msRequestFullscreen) {
    docelem.msRequestFullscreen();
  }
}
document.onclick = function () {
  if(fs_status() == (-1)){
    var conf = confirm("Fullscreen ON?");
    if (conf == true) {
      setFullScreen();
      screen.orientation.lock('landscape');
      var frameHeight = window.screen.height;
      var frameWidth = window.screen.width;
      var frameWidthHalf = Math.round(frameWidth/2);
      var siteRoot = location.protocol + '//' + location.hostname + ':8090' + '/';
      document.getElementById('right_iframe').src = siteRoot + "stream?topic=/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
      document.getElementById('left_iframe').src  = siteRoot + "stream?topic=/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
    }
  }else{
    var conf = confirm("Fullscreen OFF?");
    if(conf == true){
      setFullScreen();
      window.screen.unlockOrientation();
    }
  }
}
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
    name : '/head_position_controller/command',
    messageType : 'std_msgs/Float64'
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