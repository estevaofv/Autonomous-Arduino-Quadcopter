(Welcome Google Science Fair - Autonomous-Arduino-Quadcopter - Kevin Sheridan)
**I couldnt fit all of the information on my GSF page so here is some more!**
=============================
Further explanation of project from a software perspective:

**Quadcopter ROS Packages/quadcopter_ros/src/serial_node.cpp**
	this program is responsible for determining linear rate of quadcopter from angle and change in position, and this program takes that data along with commands and relays it over UART serial to the quadcopter's flight controller to be processed into motor commands.
	
**Quadcopter ROS Packages/quadcopter_ros/src/curiosity_node.cpp**
	this program is running an OpenCV haar cascade classifier to detect faces in a frame from my webcam. Once a face is detected its position is extrapolated and place on the map in the form of an arrow.
	
**Quadcopter ROS Packages/quadopter_ros/src/explorer_node.cpp**
	this program is responsible for giving the quadcopter curiosity (even though it is not called curiosity :)) this program runs an algorithm which extracts frontiers from the occupancy grid and logically determines a goal to travel to depending on how unknown the environment is.
	I am currently rewriting and modifying the algorithm to improve speed and efficiency, so if you see a file called "Quadcopter ROS Packages/quadcopter_ros/src/explorerV2_node.cpp" or "Quadcopter ROS Packages/quadcopter_ros/include/ks_explorer.cpp" those are the new and improved algorithms
	
**custom flight controller firmware**

**Flight Control Software/Quadcopter_main_rev13**
	this software is responsible for extremely low level flight control. It takes in a myriad of data like cmd_vel, imu, optical flow, sonar, and position, and processes it with over 14 PID controllers to output 4 motor commands. I decided to develop my own flight controller because there are no flight controllers that exist which can accept velocity data from a computer over serial and use them to fly.
	Developing this flight control software took me over 6 months because I had to overcome many stability issues.

