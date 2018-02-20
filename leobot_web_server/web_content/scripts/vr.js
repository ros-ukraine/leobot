var alpha, valpha, z;
      var beta, vbeta, x;
      var gamma, vgamma, y;


// setup event handler to capture the orientation event and store the most recent data in a variable

      if (window.DeviceOrientationEvent) {
        // Listen for the deviceorientation event and handle the raw data
        window.addEventListener('deviceorientation', function(eventData) {


          // alpha is the compass direction the device is facing in degrees
          alpha = eventData.alpha

          }, false);
        };



// Connecting to ROS

var ros = new ROSLIB.Ros({
    url : 'ws://192.168.1.107:9090'
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