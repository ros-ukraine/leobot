$(function(){
  var gamepadPlaceholder = {index: null, name: '[None connected]'};

  Vue.use(VueFormWizard);

  var list = new Vue({
    el: '#wizard',
    data: {
      gamepads: [gamepadPlaceholder]
    },
    methods: {
      // validateAsync: function() {
      //   // return new Promise((resolve, reject) => {
      //   //   setTimeout(() => {
      //   //   }, 1000)
      //     if (list.gamepads[0].index === null) {
      //       reject('Please select a joystick');
      //     } else {
      //       resolve(true);
      //     }
      // },

      onComplete: function(){
        alert('Yay. Done!');
      }
    }
  });

  window.addEventListener("gamepadconnected", function(e) {
    logGamepad(e, 'connected');
    list.gamepads = [];

    list.gamepads.push({index: e.gamepad.index, name: e.gamepad.id});
    noneConnected = false;
    enableNextButton();
  });

  window.addEventListener("gamepaddisconnected", function(e) {
    logGamepad(e, 'disconnected');

    var deleted = false;
    list.gamepads.forEach(function(val, i){
      if (val.index === e.gamepad.index){
        console.info("Deleting gamepad %d:%d from list", e.gamepad.index, i);
        Vue.delete(list.gamepads, i);
        deleted = true;
      }
    });

    if (list.gamepads.length === 0) {
      list.gamepads.push(gamepadPlaceholder);
      disableNextButton();
    }

    if (!deleted) {
      console.error("Cannot delete the gamepad: ", e.gamepad);
    }
  });

  function logGamepad(e, state) {
    console.info("Gamepad %s at index %d: %s. %d buttons, %d axes.",
    state, e.gamepad.index, e.gamepad.id,
    e.gamepad.buttons.length, e.gamepad.axes.length);
  }

  function getButtonNext() {
    return $('#wizard .wizard-footer-right button');
  }

  function disableNextButton() {
    getButtonNext().attr("disabled", true);
  }

  function enableNextButton() {
    getButtonNext().removeAttr("disabled");
  }

  disableNextButton();
})
