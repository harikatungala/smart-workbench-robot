# Smart Workbench Assistant Robot

## Overview
This project is a Bluetooth-triggered autonomous workbench robot designed for laboratory environments. The robot starts on receiving a command and navigates between predefined bench positions to assist in transporting lab equipment.

It uses an ultrasonic sensor to detect obstacles, stops when an obstruction is present, and resumes movement once the path is clear. After completing its route, the robot returns to its initial position.



## Features
- Bluetooth-triggered start command
- Autonomous navigation between benches
- Real-time obstacle detection and pause/resume
- Relay-based motor control
- Automatic return to starting position



## Components Used
- Arduino
- HC-05 Bluetooth module
- Ultrasonic sensor (HC-SR04)
- Relay module
- DC motors
- Motor driver (for head movement)



## Working Principle
1. The robot starts when a Bluetooth command ("start") is received.
2. It follows a predefined path to visit multiple bench locations.
3. The ultrasonic sensor continuously monitors distance.
4. If an obstacle is detected within a threshold (~20 cm), the robot stops.
5. Movement resumes automatically once the path is clear.
6. After visiting all benches, the robot returns to its initial position.


## Applications
- Laboratory assistance
- Automated material transport
- Educational robotics projects


## Future Improvements
- Replace delay-based control with real-time (millis) logic
- Add path decision (left/right) instead of waiting
- Improve navigation using sensors or mapping
- Implement better motor control using drivers instead of relays
