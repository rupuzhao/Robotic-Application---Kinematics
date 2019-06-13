# Robotic-Application---Kinematics

Note: This program is made for Arduino hardware robot

This lab performs mainly two kinematics motion which are forward kinematics and inverse kinematics

Forward Kinematics
    Apply a sequence of motor controls to an initial robot
    pose to find the final robot pose.
Inverse Kinematics
    Find the sequence of motor controls applied to an initial
    robot pose to reach a given final robot pose.
    
    
 Speed of wheel: 
wheelSpeeds[0] = (1 / 32) / (leftTime2 - leftTime1) * 1000;
wheelSpeeds[1] = (1 / 32) / (rightTime2 - rightTime1) * 1000;
(This is calculation the speed of left wheel and right wheel. Using the difference of the begin time and the end time (microseconds), and then divide 1/32 revolution. Finally we can get the speed of wheel.)


setSpeedsIPS(ipsLeft, ipsRight);
float d = 2.61;
float leftSpeed = ipsLeft / (3.14 * d);
float rightSpeed = ipsRight / (3.14 * d);
（According the diameter of wheel equals to 2.61, we can easily get the perimeter by (3.14 * d). Using the robot runs inches per second divided by the perimeter that we can get the parameter of the robot moves the rotation per second. Finally we put those parameter in setSpeedsRPS()）


setSpeeds(leftSpeed, rightSpeed);
（making use of the calibrate table and find the microsecond value from the table. The main function of his equation is matching the microsecond value and the IPS value）

