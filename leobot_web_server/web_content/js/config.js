$(function(){
  var pitchThreshold = 0.1;
  var gamepads = [];
  var gamepadIndex;
  var initialGamepadAxes;
  const listPlaceholder = { index: null, name: "[None connected]" };

  const configTabIndex = 1;
  const checkTabIndex = 2;
  const finishTabIndex = 3;
  const keypressTimeout = 500;
  var lastKeypressTimestamp = Date.now();
  const noneConfiguredString = "[None]";
  const initialConfiguration = [
      { role: "forward" },
      { role: "backward" },
      { role: "left" },
      { role: "right" }];
  const finishRedirectionUrl = "/index.html";

  // Current configuration
  var configuration;
  var currentConfigStep;

  Vue.use(VueFormWizard);

  var vue = new Vue({
    el: "#wizard",
    data: {
      gamepads: [listPlaceholder],
      buttonRole: "",
      configuredString: "",
      userConfiguration: null
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
        if (currentConfigStep >= configuration.length-1) {
          return true;
        }

        currentConfigStep++;
        askForButton(this, currentConfigStep);
        resetActuometer();
        return false;
      },

      onChange: function(prevIndex, nextIndex) {
        // When user goes back to config tab
        switch (nextIndex) {
          case configTabIndex:
            if (prevIndex > configTabIndex) {
              this.showButtonsConfig();
            }
            break;

          case checkTabIndex:
            console.log("Gamepad configuration results:", configuration);
            var userConfiguration = [];

            configuration.forEach(function(c) {
              var role = capitalizeString(c.role);
              var configuredString = c.type ? capitalizeString(c.type) + " #" + c.index : noneConfiguredString;
              var currentDeviation = getDeviationPercentage(c.pitchedValue, c.releasedValue, false);
              var direction = !currentDeviation ? "" : currentDeviation > 0 ? "↷" : "↶";
              var deviationPercentage = currentDeviation ? Math.abs(currentDeviation).toFixed(1) + "%" : "";

              userConfiguration.push([role, configuredString, direction, deviationPercentage]);
            });

            this.$set(this, "userConfiguration", userConfiguration);
            break;

          case finishTabIndex:
            break;
        }
      },

      onComplete: function() {
        window.location.href = finishRedirectionUrl;
      }
    }
  });

  window.addEventListener("gamepadconnected", function(e) {
    logGamepad(e, "connected");
    vue.gamepads = [];
    vue.gamepads.push({ index: e.gamepad.index, name: e.gamepad.id });
    gamepads[e.gamepad.index] = e.gamepad;
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

  $(document).on("keydown", function(e) {
    var tabs = vue.$refs.tabs;

    callIfReady(function(e, tabs) {
      switch (e.which) {
        case 8:
          tabs.prevTab();
          break;

        case 13:
        case 32:
          tabs.nextTab();
          break;
      }
    }, e, tabs);
  });

  function callIfReady(f, ...args) {
    var now = Date.now();

    if (now - lastKeypressTimestamp > keypressTimeout) {
      f.apply(null, args);
      lastKeypressTimestamp = now;
    }
  }

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
    vue.configuredString = noneConfiguredString;
  }

  function updateActuometer(){
    var gamepad;
    var initialGamepad = getInitialGamepad();
    var navGamepads = navigator.getGamepads();
    var continueAnimation = true;

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

        if (absPitch >= maxAbsPitch) {
          configEntry.type = "axis";
          configEntry.index = i;
          configEntry.pitchedValue = a;
          maxAbsPitch = absPitch;
        }

        updateConfiguredMessage(absPitch);
      }
    });

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
        callIfReady(function(v) {
          v.$refs.tabs.nextTab();
        }, vue);
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
        var currentDeviation = getDeviationPercentage(currentPitch, configEntry.releasedValue);
        var maxDeviation = getDeviationPercentage(configEntry.pitchedValue, configEntry.releasedValue);

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

  function getDeviationPercentage(pitch, initialPitch, absolute = true) {
    var pitchDifference = pitch - initialPitch;
    var adjustedPitchDifference = absolute ? Math.abs(pitchDifference) : pitchDifference;
    return 100 * adjustedPitchDifference;
  }

  function getInitialGamepad() {
    return gamepads[gamepadIndex];
  }

  function setActuometerPercentage(className, percentage) {
    $(".actuometer." + className + " .overlap").css("margin-left", percentage + "%");
  }

  function resetConfiguration() {
    // Deep copy of array objects
    configuration = $.map(initialConfiguration,
      function (obj) {
        return $.extend(true, {}, obj);
      });
    currentConfigStep = 0;
    resetConfigurationStep();
  }

  function resetConfigurationStep() {
    configuration[currentConfigStep] = Object.assign({}, initialConfiguration[currentConfigStep]);
    resetActuometer();
  }

  $("#reset").click(resetConfigurationStep);
  disableNextButton();
})

function capitalizeString(s) {
  return s.charAt(0).toUpperCase() + s.slice(1);
}
