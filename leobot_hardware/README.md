# Update messages

In order to update message files please run

```bash
rosrun leobot_hardware generate_messages.sh
```

# Cross-system building

For Atollic IDE create this symbolic link in order to build in Windows and Linux

```bash
# Go to Atollic installation folder
atollic_bin=/opt/Atollic_TrueSTUDIO_for_STM32_x86_64_9.0.0/ARMTools/bin

#Create symbolic link
sudo ln -s $atollic_bin/arm-atollic-eabi-objcopy $atollic_bin/arm-atollic-eabi-objcopy.exe
```

After that you should be able to compile latest source code.

