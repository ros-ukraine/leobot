var frameHeight = window.innerHeight;
var frameWidth = window.innerWidth;
var frameWidthHalf = Math.round(frameWidth/2);
document.getElementById('right_iframe').src = "http://192.168.1.107:8090/stream?topic=/leobot/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
document.getElementById('left_iframe').src = "http://192.168.1.107:8090/stream?topic=/leobot/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;

var d = document.getElementById("elem");
d.innerHTML = 0 + " " + 1;


function imusnapshot() {

     var alpha_radian = ((alpha + 360) / 360 * 2 * Math.PI) % (2 * Math.PI);
     console.log(alpha_radian);
        d.innerHTML = alpha_radian;

     var imuMessage = new ROSLIB.Message({
         data : alpha_radian
     });

     headControl.publish(imuMessage);
}
setInterval(function(){
              imusnapshot();
           }, 5000);