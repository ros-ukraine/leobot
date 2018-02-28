var frameHeight = window.innerHeight;
var frameWidth = window.innerWidth;
var frameWidthHalf = Math.round(frameWidth/2);
document.getElementById('right_iframe').src = "http://0.0.0.0:8090/stream?topic=/leobot/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
document.getElementById('left_iframe').src = "http://0.0.0.0:8090/stream?topic=/leobot/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;