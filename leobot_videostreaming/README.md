After start PyCharm and download all changes from F#28_videostreaming you must:

1) Install all dependencys from package.xml. For this you need go to the ~/workspace/leobot/base/src
    and run command: "sudo apt-get update" and than "depkinetic"

2) Install Firefox in Dokcer container. For this you need run "sudo apt-get install firefox".
    For start Firefox use command: "firefox".

3) Run Gazebo with Artgallery.world. For this use command: "roslaunch leobot_launch simulation.launch world_file:=artgallery"

4) Start videostreaming server use command: "rosrun web_video_server web_video_server"

5) Now you can open index.html file in Firefox from PyCharm use icon in top-right angle PyCharm IDE

CSS issues:
Iframe add few pixels to contained pictures  ...