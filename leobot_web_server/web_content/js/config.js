$(function(){
  var pitchThreshold = 0.1;
  var gamepads = [];
  var gamepadIndex;
  var initialGamepadAxes;
  var listPlaceholder = { index: null, name: "[None connected]" };

  var keypressTimeout = 1000;
  var lastEnterHitTimestamp = Date.now();
  var initialConfiguration = [
      { role: "forward" },
      { role: "backward" },
      { role: "left" },
      { role: "right" }];

  // Current configuration
  var configuration;
  var currentConfigStep;
  var lastEnterHitTimestamp;
  var configTabIndex;

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
        resetConfiguration();
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
    initialGamepadAxes = e.gamepad.axes;
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

  $(document).on("keypress", function(e) {
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

  function resetActuometer() {
    var pitchThresholdPercentage = 100 * pitchThreshold;
    setActuometerPercentage("momentary", pitchThresholdPercentage);
    setActuometerPercentage("maximum", pitchThresholdPercentage);
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
      console.warn("Selected gamepad is unavailable");
      alert("Sorry, Houston. This joystick was disconnected.");
      vue.$refs.tabs.reset();
      resetConfiguration();
      return;
    }

    var configEntry = getCurrentConfigEntry();

    gamepad.axes.forEach(function(a, i) {
      var pitch = a - initialGamepadAxes[i];
      var absPitch = Math.abs(pitch);

      if (absPitch > pitchThreshold && i!==9) {
        if (!configEntry.releasedValue) {
          configEntry.releasedValue = configEntry.pitchedValue = initialGamepadAxes[i];
        }

        var maxAbsPitch = Math.abs(configEntry.releasedValue - configEntry.pitchedValue);

        // console.log(i, maxAbsPitch, absPitch);
        // console.log(i, maxAbsPitch);
        // console.log(configEntry);
        // console.log(configEntry.releasedValue, configEntry.pitchedValue);

        if (absPitch >= maxAbsPitch) {
          configEntry.type = "axis";
          configEntry.index = i;
          // configEntry.releasedValue = a;
          configEntry.pitchedValue = a;
          maxAbsPitch = absPitch;
        }

        updateConfiguredMessage(absPitch);
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

  function updateConfiguredMessage(currentPitch = null){
    var configEntry = getCurrentConfigEntry();
    var index = configEntry.index;
    var type = configEntry.type;
    var messageString = "";

    switch (type) {
      case "button":
        break;

      case "axis":
        // console.log(`zzz ${index} ${initialGamepadAxes[index].toFixed(2)} ${configEntry.pitchedValue.toFixed(2)}`);
        // var initialPitch = initialGamepadAxes[index];

        // showPitch(, pitch, initialPitch);
        var currentDeviation = getDeviationPercentage(currentPitch, configEntry.releasedValue);
        var maxDeviation = getDeviationPercentage(configEntry.pitchedValue, configEntry.releasedValue);

        // console.log(initialPitch, pitch, maxDeviation);
        // console.log(currentDeviation, maxDeviation);

        setActuometerPercentage("momentary", currentDeviation);
        setActuometerPercentage("maximum", maxDeviation);

        messageString = " " + maxDeviation.toFixed(1) + "%";
        break;

      default:
        console.error("Unknown gamepad sensor type: " + type);
    }

    var messageString = type + " #" + index + messageString;

    vue.configuredString = messageString;
  }

  function getDeviationPercentage(pitch, initialPitch) {
    return 100 * Math.abs(pitch - initialPitch);
  }

  function getInitialGamepad() {
    return gamepads[gamepadIndex];
  }

  function setActuometerPercentage(className, percentage) {
    $(".actuometer." + className).width(percentage + "%");
  }

  function resetConfiguration() {
    configuration = initialConfiguration;
    currentConfigStep = 0;
    configTabIndex = 1;
    resetActuometer();
  }

  disableNextButton();
})
