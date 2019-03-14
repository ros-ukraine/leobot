$(function(){
  var pitchThreshold = 0.1;
  var gamepads = [];
  var gamepadAxes;
  var gamepadIndex;
  var listPlaceholder = { index: null, name: "[None connected]" };
  var configuration = [
    { role: "forward" },
    { role: "backward" },
    { role: "left" },
    { role: "right" }
  ];
  var currentConfigStep = 0;
  var lastEnterHitTimestamp = Date.now();
  var keypressTimeout = 1000;
  var configTabIndex = 1;

  Vue.use(VueFormWizard);

  var vue = new Vue({
    el: "#wizard",
    data: {
      // gamepads: [{ index: 1, name: "[None connected 1]" }, { index: 2, name: "[None connected 2]" }, { index: 3, name: "[None connected] 3" }],
      gamepads: [listPlaceholder],
      buttonRole: "",
      configuredString: "[None]"
    },
    methods: {
      gamepadClickHandler: function(e) {
        target = $(e.currentTarget);
        parent = target.parent();
        parent.children("a").removeClass("active");
        target.addClass("active");

        var position = target.prevAll().length;
        gamepadIndex = gamepads[position].index;
      },

      showButtonsConfig: function() {
        console.log("Selected gamepad: ", getInitialGamepad());
        askForButton(this, 0);
        requestAnimationFrame(updateActuometer);
        return true;
      },

      askNextButton: function() {
        currentConfigStep++;

        if (currentConfigStep >= configuration.length) {
          return true;
        }

        askForButton(this, currentConfigStep);
        return false;
      },

      onChange: function(prevIndex, nextIndex) {
        // When user goes back to config tab
        if (nextIndex === configTabIndex && prevIndex > configTabIndex) {
          currentConfigStep = 0;
          this.showButtonsConfig();
        }
      },

      onComplete: function() {
        alert("Yay. Done!");
      }
    }
  });

  window.addEventListener("gamepadconnected", function(e) {
    logGamepad(e, "connected");
    vue.gamepads = [];
    vue.gamepads.push({ index: e.gamepad.index, name: e.gamepad.id });
    // vue.gamepads.push({ index: e.gamepad.index+1, name: e.gamepad.id+" Y" });
    // vue.gamepads.push({ index: e.gamepad.index+2, name: e.gamepad.id+" Z" });
    gamepads[e.gamepad.index] = e.gamepad;
    // gamepads[e.gamepad.index+1] = "Two";
    // gamepads[e.gamepad.index+2] = "Three";
    gamepadAxes = e.gamepad.axes;
    gamepadIndex = e.gamepad.index;
    noneConnected = false;
    enableNextButton();
  });

  window.addEventListener("gamepaddisconnected", function(e) {
    logGamepad(e, "disconnected");

    var deleted = false;
    vue.gamepads.forEach(function(val, i) {
      if (val.index === e.gamepad.index) {
        console.info("Deleting gamepad %d:%d from list", e.gamepad.index, i);
        Vue.delete(vue.gamepads, i);
        gamepads.splice(e.gamepad.index, 1);
        deleted = true;
      }
    });

    if (vue.gamepads.length === 0) {
      vue.gamepads.push(listPlaceholder);
      disableNextButton();
    }

    if (!deleted) {
      console.error("Cannot delete the gamepad: ", e.gamepad);
    }
  });

  $(document).on("keypress",function(e) {
    var now = Date.now();
    if (e.which == 13 && now - lastEnterHitTimestamp > keypressTimeout) {
      vue.$refs.tabs.nextTab();
      lastEnterHitTimestamp = now;
    }
  });

  function logGamepad(e, state) {
    console.info("Gamepad %s at index %d: %s. %d buttons, %d axes.",
    state, e.gamepad.index, e.gamepad.id,
    e.gamepad.buttons.length, e.gamepad.axes.length);
  }

  function getButtonNext() {
    return $("#wizard .wizard-footer-right button");
  }

  function disableNextButton() {
    getButtonNext().attr("disabled", true);
  }

  function enableNextButton() {
    getButtonNext().removeAttr("disabled");
  }

  function askForButton(vue, index) {
    vue.buttonRole = configuration[index].role;
  }

  function updateActuometer(){
    var gamepad;
    var initialGamepad = getInitialGamepad();
    var navGamepads = navigator.getGamepads();

    // getGamepads() returns a GamepadList which is not really an Array
    // and we cannot iterate over it with forEach method
    for (var i=0; i<navGamepads.length; i++){
      var g = navGamepads[i];
      if (g && g.index === gamepadIndex) {
        gamepad = g;
      }
    }

    if (!gamepad) {
      console.error("Selected gamepad is unavailable");
    }

    var configEntry = getCurrentConfigEntry();

    gamepad.axes.forEach(function(a, i) {
      var pitch = a - gamepadAxes[i];

      if (Math.abs(pitch) > pitchThreshold) {
        configEntry.type = "axis";
        configEntry.index = i;
        configEntry.releasedValue = a;
        configEntry.pitchedValue = pitch;
        updateConfiguredMessage();
      }
    });

    // var values = [].concat(gamepad.buttons.value, gamepad.axes);
    gamepad.buttons.forEach(function(button, index){
      var pressed = button.value;

      if (pressed) {
        // Prevent duplicate messages
        if (index !== configEntry.index) {
          console.log("Last pressed button ", index);
        }
        configEntry.type = "button";
        configEntry.index = index;
        updateConfiguredMessage();
      }
    });

    requestAnimationFrame(updateActuometer);
  }

  function getCurrentConfigEntry(){
    return configuration[currentConfigStep];
  }

  function updateConfiguredMessage(){
    var configEntry = getCurrentConfigEntry();
    var type = configEntry.type;

    switch (type) {
      case "button":
        break;

      case "axis":
        $(".actuometer.maximum").width("" + Math.abs(configEntry.pitchedValue)*100 + "%");
        break;

      default:
        console.error("Unknown gamepad sensor type: " + type);
    }

    vue.configuredString = type + " #" + configEntry.index;
  }

  function getInitialGamepad() {
    return gamepads[gamepadIndex];
  }

  disableNextButton();
})
