var a = window.innerHeight;
var b = window.innerWidth;
var c = Math.round(b/2);
console.log(a,b,c);
document.getElementById('right_iframe').src = "http://0.0.0.0:8080/stream?topic=/leobot/stereocamera/right/image_raw&width="+c+"&height="+a;
document.getElementById('left_iframe').src = "http://0.0.0.0:8080/stream?topic=/leobot/stereocamera/left/image_raw&width="+c+"&height="+a;
document.addEventListener("orientationchange", function(event){
    switch(window.orientation)
    {
        case -90: case 90:
            /* Device is in landscape mode */
            break;
        default:
            /* Device is in portrait mode */
    }
});