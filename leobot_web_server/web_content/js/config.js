$(function(){
  var pitchThreshold = 0.1;
  var gamepads = [];
  var gamepadIndex = null;
  var initialGamepadAxes;
  const listPlaceholder = { index: null, name: "[None connected]" };
  const actuometerLowColor = [100, 100, 160];
  const actuometerHighColor = [0, 160, 0];
  const localStorageKey = "Gamepad configuration";

  const TABS = {
    select: 0,
    config: 1,
    check: 2,
    finish: 3
  };

  const keypressTimeout = 500;
  var lastKeypressTimestamp = Date.now();
  const noneConfiguredString = "[None]";
  const initialConfiguration = [
      { role: "forward" },
      { role: "backward" },
      { role: "left" },
      { role: "right" }];
  const finishRedirectionUrl = "/vr.html";

  // Current configuration
  var configuration;
  var currentConfigStep = null;

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
        requestAnimationFrame(updateConfig);

        var lowRgbColorString = getColorRgbString(actuometerLowColor);
        var highRgbColorString = getColorRgbString(actuometerHighColor);
        var colorGradientString = `linear-gradient(to right, ${lowRgbColorString}, ${highRgbColorString})`;
        $(".actuometer.momentary").css("background-image", colorGradientString);

        return true;
      },

      askNextButton: function() {
        if (currentConfigStep >= configuration.length-1) {
          currentConfigStep = null;
          return true;
        }

        currentConfigStep = currentConfigStep === null ? 0 : 1 + currentConfigStep;
        askForButton(this, currentConfigStep);
        resetActuometer();
        return false;
      },

      onChange: function(prevIndex, nextIndex) {
        // When user goes back to config tab
        switch (nextIndex) {
          case TABS.select:
            initGamepadSelection();
            break;

          case TABS.config:
            if (prevIndex > TABS.config) {
              this.showButtonsConfig();
            }

            var gamepad = getCurrentGamepad();

            initialGamepadAxes = [];
            gamepad.axes.forEach(function(a) {
              var axis = null;
              // Ignore axes which return unuseful data out of the region [-1; 1]
              // i.e. thumbstick angle in polar coordinate system
              if (a >= -1 && a <= 1) {
                axis = a;
              }
              initialGamepadAxes.push(axis);
            });

            console.log("Initial gamepad axes values:", initialGamepadAxes);
            break;

          case TABS.check:
            console.log("Gamepad configuration results:", configuration);
            var userConfiguration = [];

            configuration.forEach(function(c) {
              var role = capitalizeString(c.role);
              var configuredString = c.type ? capitalizeString(c.type) + " #" + c.index : noneConfiguredString;
              var currentTilt = getTiltPercentage(c.pitchedValue, c.releasedValue, false);
              var direction = !currentTilt ? "" : currentTilt > 0 ? "↷" : "↶";
              var tiltPercentage = currentTilt ? Math.abs(currentTilt).toFixed(1) + "%" : "";

              userConfiguration.push([role, configuredString, direction, tiltPercentage]);
            });

            this.$set(this, "userConfiguration", userConfiguration);
            break;

          case TABS.finish:
            localStorage.setItem(localStorageKey, JSON.stringify(configuration));
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

        case 82:
          resetConfigurationStep();
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

  function initGamepadSelection() {
    requestAnimationFrame(selectGamepadWithPressedButton);
  }

  function selectGamepadWithPressedButton() {
    var gamepads = getGamepadsAsArray();
    var index = null;

    gamepads.forEach(function(gamepad) {
      gamepad.buttons.forEach(function(button) {
        if (button.value) index = gamepad.index;
      });
    });

    if (index !== null) {
      gamepadIndex = index;
      lastKeypressTimestamp = Date.now();
      currentConfigStep = null;
      vue.$refs.tabs.nextTab();
    } else {
      requestAnimationFrame(selectGamepadWithPressedButton);
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
    showMomentaryPercentage(pitchThresholdPercentage);
    showMaximumPercentage(pitchThresholdPercentage);
    vue.configuredString = noneConfiguredString;
  }

  function updateConfig(){
    var gamepad = getCurrentGamepad();
    var configEntry = getCurrentConfigEntry();

    // Prevent errors if requestAnimationFrame() called the function
    // when all buttons are already configured (config results step)
    if (!configEntry) return;

    gamepad.axes.forEach(function(a, i) {
      // Can be null
      var axis = initialGamepadAxes[i];
      var pitch = a - axis;
      var absPitch = Math.abs(pitch);

      if (axis !== null && absPitch > pitchThreshold) {
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

        updateConfigurationMessage(absPitch);
      }
    });

    gamepad.buttons.forEach(function(button, index){
      var pressed = button.value;

      if (pressed) {
        // Prevent duplicate messages
        if (index !== configEntry.index) {
          console.log("Last pressed button ", index);
        }
       // Erase the previous axis data for this step
        resetConfigurationStep();
        // Get the clean entry because now the configEntry contains a symbolic link to the old object
        configEntry = getCurrentConfigEntry();
        configEntry.type = "button";
        configEntry.index = index;
        callIfReady(function(v) {
          v.$refs.tabs.nextTab();
        }, vue);
        // Do not show the configured value for fraction of second before querying the next one
        // updateConfigurationMessage();
      }
    });

    requestAnimationFrame(updateConfig);
  }

  function getCurrentGamepad() {
    var gamepad;
    var initialGamepad = getInitialGamepad();
    var gamepads = getGamepadsAsArray();

    // Use the last gamepad - which was attached later
    gamepads.forEach(function(g) {
      if (g.index === gamepadIndex) gamepad = g;
    });

    if (!gamepad) {
      console.warn("Selected gamepad is unavailable");
      alert("Sorry, Houston. This joystick was disconnected.");
      vue.$refs.tabs.reset();
      resetConfiguration();
      return;
    }

    return gamepad;
  }

  function getCurrentConfigEntry(){
    return configuration[currentConfigStep];
  }

  function updateConfigurationMessage(currentPitch = null){
    var configEntry = getCurrentConfigEntry();
    var index = configEntry.index;
    var type = configEntry.type;
    var messageString = "";

    switch (type) {
      case "button":
        break;

      case "axis":
        var currentTilt = getTiltPercentage(currentPitch, configEntry.releasedValue);
        var maxTilt = getTiltPercentage(configEntry.pitchedValue, configEntry.releasedValue);

        showMomentaryPercentage(currentTilt);
        showMaximumPercentage(maxTilt);

        messageString = " " + maxTilt.toFixed(1) + "%";
        break;

      default:
        console.error("Unknown gamepad sensor type: " + type);
    }

    var messageString = type + " #" + index + messageString;

    vue.configuredString = messageString;
  }

  function getTiltPercentage(pitch, initialPitch, absolute = true) {
    var pitchDifference = pitch - initialPitch;
    var adjustedPitchDifference = absolute ? Math.abs(pitchDifference) : pitchDifference;
    return 100 * adjustedPitchDifference;
  }

  function getInitialGamepad() {
    return gamepads[gamepadIndex];
  }

  function showMomentaryPercentage(momentaryPercentage) {
    setActuometerPercentage("momentary", momentaryPercentage);
  }

  function showMaximumPercentage(maxPercentage) {
    setActuometerPercentage("maximum", maxPercentage);

    var color = getColorGradientValue(actuometerHighColor, actuometerLowColor, maxPercentage/100);
    var colorRgbString = getColorRgbString(color);
    $(".actuometer.maximum").css("background-color", colorRgbString);
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
  initGamepadSelection();
})

function capitalizeString(s) {
  return s.charAt(0).toUpperCase() + s.slice(1);
}

function getColorGradientValue(color1, color2, weight) {
    var w = weight * 2 - 1;
    var w1 = (w/1+1) / 2;
    var w2 = 1 - w1;
    var rgb = [Math.round(color1[0] * w1 + color2[0] * w2),
        Math.round(color1[1] * w1 + color2[1] * w2),
        Math.round(color1[2] * w1 + color2[2] * w2)];
    return rgb;
}

function getColorRgbString(colorRgbArray) {
  return `rgb(${colorRgbArray[0]}, ${colorRgbArray[1]}, ${colorRgbArray[2]})`;
}

function getGamepadsAsArray() {
  var navGamepads = navigator.getGamepads();
  var gamepads = [];

  // getGamepads() returns a GamepadList which is not really an Array
  // and we cannot iterate over it with forEach method
  for (var i=0; i<navGamepads.length; i++){
    var g = navGamepads[i];
    if (g) {
      gamepads.push(g);
    }
  }

  return gamepads;
}
