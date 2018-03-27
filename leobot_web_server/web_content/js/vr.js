var frameHeight = window.innerHeight;
var frameWidth = window.innerWidth;
var frameWidthHalf = Math.round(frameWidth/2);
var siteRoot = location.protocol + '//' + location.hostname + ':8090' + '/';

document.getElementById('right_iframe').src = siteRoot + "stream?topic=/leobot/stereocamera/right/image_raw&width="+frameWidthHalf+"&height="+frameHeight;
document.getElementById('left_iframe').src  = siteRoot + "stream?topic=/leobot/stereocamera/left/image_raw&width="+frameWidthHalf+"&height="+frameHeight;