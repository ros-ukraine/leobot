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

//gyro_test
var d = document.getElementById("elem");
d.innerHTML = 0 + " " + 1;

function handleOrientation(event) {
    console.log("hello");
  var x = event.beta;  // In degree in the range [-180,180]
  var y = event.gamma; // In degree in the range [-90,90]
  var z = event.alpha;
  var absolute = event.absolute;
  console.log(x,y,z);
  d.innerHTML = x + ", " + y + ", " + z;

  }

window.addEventListener('deviceorientation', handleOrientation);